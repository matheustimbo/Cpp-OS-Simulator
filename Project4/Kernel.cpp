#pragma once 
#include <vector>
#include <iostream>
#include <string>
#include "Process.cpp"
#include "Scheduler.cpp"
#include "Enums.cpp"
#include "MemoryManager.cpp"
#include "Debug.cpp"

using namespace std;

class Kernel {

    vector<Process*> process_table;
    Scheduler* scheduler;
    MemoryManager* memory_manager;
    Debug* debug;

public:
    Kernel(int core_number, int dQuantum, enum_scheduling_algorithm scheduling_algorithm, enum_memory_allocation_algorithm pMemoryAllocationAlgorithm, int pTotal_installed_memory) {
        scheduler = new Scheduler(scheduling_algorithm, dQuantum, core_number, memory_manager);
        memory_manager = new MemoryManager(pTotal_installed_memory, pMemoryAllocationAlgorithm);
        debug = new Debug(scheduler, memory_manager, process_table);
    }

    void run() {
        thread schedulerThread(&Scheduler::run, getScheduler());
        thread memoryManagerThread(&MemoryManager::run, getMemoryManager());
        thread debugThread(&Debug::runDebug, getDebug());
        schedulerThread.join();


        //memoryManagerThread.join();
    }

    Debug* getDebug(){
        return debug;
    }

    void kill_process(Process* pProcess) {
        this->scheduler->removeProcessById(pProcess->getProcessId());
        pProcess->setState(enum_process_state::aborted);
    }

    void load_scheduler() {
        for (int i = 0; i < process_table.size(); i++) {
            scheduler->insert_process(process_table[i]);
        }
    }

    void create_process(int id, int time) {
        Process* process = new Process(id, time, memory_manager);
        process_table.push_back(process);
        scheduler->insert_process(process);
    }

    vector<Process*> getProcessTable() {
        return process_table;
    }

    void printProcessTable() {
        cout << "--Processos--" << endl;
        for (int i = 0; i < process_table.size(); i++) {
            cout << "id: ";
            cout << process_table[i]->getProcessId() << endl;
            cout << "time: ";
            cout << process_table[i]->getReamainingTime() << endl;
        }
    }

    Scheduler* getScheduler() {
        return scheduler;
    }

    MemoryManager* getMemoryManager() {
        return memory_manager;
    }


    MemoryBlock* memory_allocation(int required_amount) {
        return this->memory_manager->malloc(required_amount);
    }

    void free_memory(MemoryBlock* pMemoryBlock) {
        this->memory_manager->free(pMemoryBlock);
    }

};
