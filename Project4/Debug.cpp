#pragma once
#include "Process.cpp"
#include "Scheduler.cpp"
#include "MemoryManager.cpp"

class Debug {
    Scheduler* scheduler;
    MemoryManager* memoryManager;
    vector<Process*> process_table;
public:
    Debug(Scheduler* pScheduler, MemoryManager* pMemoryManager, vector<Process*> pProcess_table) {
        scheduler = pScheduler;
        memoryManager = pMemoryManager;
        process_table = pProcess_table;
    }

    void runDebug () {
        while (true) {
            print_queue();
            print_cores();
            print_blocks();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    void print_blocks() {
        cout<<"BLOCOS DE MEMORIA: -------------"<<endl;
        int id = 0;
        cout<<"Memory Block: [";
        for(MemoryBlock* memoryBlock : memoryManager->getMemory()){

            cout <<"[ id: " << id << " , ProcessId: " << getMemoryProcess(memoryBlock)->getProcessId() << " , Memoria: " << memoryBlock->occupied_size << "/" << memoryBlock->total_block_size << " ],";

            id++;
        }
        cout <<" ]" <<endl <<endl;
    }

    Process* getMemoryProcess (MemoryBlock* pMemoryBlock){
        for(Process* process : process_table){
            for(MemoryBlock* memoryBlock : process->getMemoryPointers()){
                if(memoryBlock == pMemoryBlock){
                    return process;
                }
            }
        }
    }

    void print_queue() {
        cout << "FILA: ----------" << endl;
        for (Process* process : scheduler->getReadyQueue()) {
            cout << "[Id: " << process->getProcessId() << " , Reamaining time: " <<  process->getReamainingTime() << ", total time: " << process->getTotalTime();;
            if (scheduler->getSchedulingAlgorithm() == enum_scheduling_algorithm::round_robin) {
                cout << ", quantum: " << process->getQuantumCount() << "/" << scheduler->dQuantum;
            }
            cout << "]";
            //<< endl;
        }
        cout << "----------" << endl <<endl;
    }

    void print_cores() {
        cout << "CORES: (no debug) -------------------" << endl;
        int id = 0;
        for (Core* core : scheduler->getCpu()->getCores()) {
            cout << "[Core ";
            cout << id;
            cout << ", Process:";
            if (core->getCurrentProcess() == NULL) {
                cout << "CORE_VAZIO]";
            } else {
                cout << "[id: " << core->getCurrentProcess()->getProcessId() << ", Reamaining time: " << core->getCurrentProcess()->getReamainingTime() << ", total time:" << core->getCurrentProcess()->getTotalTime();
                if (scheduler->getSchedulingAlgorithm() == enum_scheduling_algorithm::round_robin) {
                    cout << ", quantum: " << core->getCurrentProcess()->getQuantumCount() << "/" << scheduler->dQuantum;
                }
                cout << "], ";
            }
            id++;
            //cout << endl;
        }
        cout << "---------------" << endl << endl;
    }
};
