#pragma once 
#include <iostream>
#include "Enums.cpp"
#include <vector>
#include "MemoryBlock.cpp"
#include "MemoryManager.cpp"

class Process {


    int process_id;
    int total_time;
    MemoryBlock* block;
    enum_process_state state;
    int reamaining_time;
    int quantum_count;
    std::vector<MemoryBlock*> memory_pointers;
    MemoryManager* memoryManager;

public:


    Process(int id, int time, MemoryManager* pMemoryManager) {
        memoryManager = pMemoryManager;
        process_id = id;
        total_time = time;
        reamaining_time = time;
        state = enum_process_state::ready;
        quantum_count = 0;
        generate_random_static_memory_call();
    }

    vector<MemoryBlock*> getMemoryPointers () {
        return memory_pointers;

    }

    void generate_random_static_memory_call() {
        try{
            int randomNumber = 1 + rand() % 4096;
            if(this->memoryManager->check_free_memory(randomNumber)){
                MemoryBlock* block = this->memoryManager->malloc(randomNumber);
                cout <<"passou do malloc " <<endl<<endl;
                if(block == NULL){
                    this->setState(enum_process_state::aborted);
                    for(MemoryBlock* memoryBlock: memory_pointers){
                        memoryManager->free(memoryBlock);
                    }
                } else {
                    block->occupied_size = randomNumber;
                    this->memory_pointers.push_back(block);
                }
            } else { //memoria cheia!!
               abort();
            }

        } catch (...) {
            throw;
        }

    }

    void generate_random_dynamic_memory_call() {
        int randomNumber = 1 + rand() % 4096;
        int randomNumberAux = 1 + rand() % 50;

        if (randomNumberAux <= 10) {
            if(this->memoryManager->check_free_memory(randomNumber)){
                MemoryBlock* block = this->memoryManager->malloc(randomNumber);
                if(block == NULL){
                    this->setState(enum_process_state::aborted);
                    for(MemoryBlock* memoryBlock: memory_pointers){
                        memoryManager->free(memoryBlock);
                    }

                } else {
                    block->occupied_size = randomNumber;
                    this->memory_pointers.push_back(block);
                }
            } else { //memoria cheia!!
                abort();
            }

        }
    }

    void abort(){
        this->setState(enum_process_state::aborted);
    }

    int getQuantumCount() {
        return quantum_count;
    }

    void setQuantumCount(int pNewQuantum) {
        quantum_count = pNewQuantum;
    }

    int getProcessId() const {

        return process_id;
    }

    void setProcessId(int processId) {
        process_id = processId;
    }

    int getTotalTime() const {
        return total_time;
    }

    void setTotalTime(int totalTime) {
        total_time = totalTime;
    }


    enum_process_state getState() const {
        return state;
    }

    void setState(enum_process_state pState) {
        state = pState;
    }

    int getReamainingTime() const {
        return reamaining_time;
    }

    void setReamainingTime(int reamainingTime) {
        reamaining_time = reamainingTime;
    }
};
