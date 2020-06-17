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
        cout<<"MEMORIA: TM: " << memoryManager->total_memory << " MO: " << memoryManager->memory_overhead << " AM: " << memoryManager->available_memory << " OM: " << memoryManager->occupied_memory << " MNA: " << memoryManager->memoria_nao_alocada << endl;
        int idBloco = 0;
        for(MemoryBlock* memoryBlock : memoryManager->getMemory()){
            cout <<"[ id: " << idBloco << " , pcID: " << getMemoryProcessId(memoryBlock) << " , MM: " << memoryBlock->occupied_size << "/" << memoryBlock->total_block_size << " ],";

            idBloco++;
        }
        cout <<" ]" <<endl <<endl;
    }

    int getMemoryProcessId (MemoryBlock* pMemoryBlock){
        Process* processoAux = NULL;
        for(Process* process : scheduler->getReadyQueue()){
            for(MemoryBlock* memoryBlock : process->getMemoryPointers()){
                if(memoryBlock == pMemoryBlock){
                    processoAux =  process;
                }
            }
        }
        if (processoAux == nullptr) {
            return -1;
        }
        else {
            return processoAux->getProcessId();
        }
    }

    void print_queue() {
        cout << "FILA: ----------" << endl;
        for (Process* process : scheduler->getReadyQueue()) {
            cout << "[Id: " << process->getProcessId() << " , RT: " <<  process->getReamainingTime() << ", TT: " << process->getTotalTime();;
            if (scheduler->getSchedulingAlgorithm() == enum_scheduling_algorithm::round_robin) {
                cout << ", QT: " << process->getQuantumCount() << "/" << scheduler->dQuantum;
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
            cout << ", PRCS:";
            if (core->getCurrentProcess() == NULL) {
                cout << "CORE_VAZIO]";
            } else {
                cout << "[id: " << core->getCurrentProcess()->getProcessId() << ", RT: " << core->getCurrentProcess()->getReamainingTime() << ", TT:" << core->getCurrentProcess()->getTotalTime();
                if (scheduler->getSchedulingAlgorithm() == enum_scheduling_algorithm::round_robin) {
                    cout << ", QT: " << core->getCurrentProcess()->getQuantumCount() << "/" << scheduler->dQuantum;
                }
                cout << "], ";
            }
            id++;
            //cout << endl;
        }
        cout << "---------------" << endl << endl;
    }
};
