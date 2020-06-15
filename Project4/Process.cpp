#pragma once 
#include <iostream>
#include "Enums.cpp"
#include <vector>
#include "MemoryBlock.cpp"
#include "Kernel.cpp"
class Process {


    int process_id;
    int total_time;
    Kernel* pKernel;
    MemoryBlock* block;
    enum_process_state state;
    int reamaining_time;
    int quantum_count;
    vector<MemoryBlock*> memory_pointers;
public:


    Process(int id, int time) {
        process_id = id;
        total_time = time;
        reamaining_time = time;
        state = enum_process_state::ready;
        quantum_count = 0;
        kernel = pKernel;
    }

    void generate_random_static_memory_call() {
        int randomNumber = 1 + rand() % 4096;
        block = this->pKernel->memory_allocation(randomNumber);
        if (block != NULL) {
            return this->pKernel->memory_allocation(NULL);
        }
        else {
            return this->pKernel->kill_process();
        }
    }

    void generate_random_dynamic_memory_call() {
        int randomNumber = 1 + rand() % 4096;
        int randomNumberAux = 1 + rand() % 50;

        if (randomNumberAux <= 10) {
            block = this->pKernel->memory_allocation(randomNumber);
            if (block != NULL) {
                return this->pKernel->memory_allocation(NULL);
            }
            else {
                return this->pKernel->kill_process();
            }
        }
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
