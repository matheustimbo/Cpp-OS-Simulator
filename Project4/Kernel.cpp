#pragma once 
#include <vector>
#include <iostream>
#include <string>
#include "Process.cpp"
#include "Scheduler.cpp"
#include "Enums.cpp"
#include "MemoryManager.cpp"

using namespace std;

class Kernel {

    vector<Process*> process_table;
    Scheduler* scheduler;
    MemoryManager* memory_manager;



    void process_control_table() {

    }



    void kill_process() {

    }

    void run_process() {

    }




public:
    Kernel(int core_number, int dQuantum, enum_scheduling_algorithm scheduling_algorithm, ) {
        scheduler = new Scheduler(scheduling_algorithm, dQuantum, core_number);
    }

    void run() {
        thread schedulerThread(&Scheduler::run, getScheduler());
        schedulerThread.join();
    }

    void load_scheduler() {
        for (int i = 0; i < process_table.size(); i++) {
            scheduler->insert_process(process_table[i]);
        }
    }

    void create_process(int id, int time) {
        Process* process = new Process(id, time);
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


    MemoryBlock memory_allocation(int required_amount) {
        return this->memory_manager->malloc(required_amount);
    }

    void free_memory(MemoryBlock pMemoryBlock) {
        this->memory_manager->free(pMemoryBlock);
    }

};
