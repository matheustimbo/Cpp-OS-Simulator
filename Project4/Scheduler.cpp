#pragma once 
#include <vector>
#include <thread>
#include "Core.cpp"
#include "Enums.cpp"
#include "Cpu.cpp"
#include "MemoryManager.cpp"

using namespace std;

class Scheduler {
    vector<Process*> ready_queue;
    enum_scheduling_algorithm scheduling_algorithm;

    MemoryManager* memoryManager;
    
public:
    Cpu* cpu;
    int dQuantum;

    Scheduler(enum_scheduling_algorithm schedulingAlgorithm, int pDQuantum, int core_number, MemoryManager* pMemoryManager) {
        scheduling_algorithm = schedulingAlgorithm;
        dQuantum = pDQuantum;
        cpu = new Cpu(core_number);
        memoryManager = pMemoryManager;
    }

    Cpu* getCpu() {
        return cpu;
    }

    vector<Process*> getReadyQueue() {
        return ready_queue;
    }

    void setReadyQueue(vector<Process*> pReadyQueue) {
        ready_queue = pReadyQueue;
    }

    enum_scheduling_algorithm getSchedulingAlgorithm() {
        return scheduling_algorithm;
    }

    void setSchedulingAlgorithm(enum_scheduling_algorithm schedulingAlgorithm) {
        scheduling_algorithm = schedulingAlgorithm;
    }

    void set_scheduling_algorithm(enum_scheduling_algorithm scheduling_algorithm) {
        this->scheduling_algorithm = scheduling_algorithm;
    }

    void runSchedulingAlgorithm() {
        int seconds = 0;
        
        while (true) {
            //cout << "thread scheduler segundo t[" << seconds << "]" << endl;
            seconds++;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            cout << "scheduling algorithm: " << getSchedulingAlgorithm() << endl;
            if (getSchedulingAlgorithm() == enum_scheduling_algorithm::fifo) {
                fifo_scheduler();
            }
            if (getSchedulingAlgorithm() == enum_scheduling_algorithm::round_robin) {
                roundrobin();
            }
            if (getSchedulingAlgorithm() == enum_scheduling_algorithm::shortest_job) {
                //shortest_job_first();
                fifo_scheduler();
            }
        }
        
    }

    void run() {
        thread scheduleThread(&Scheduler::runSchedulingAlgorithm, this);
        scheduleThread.join();
    }

    MemoryManager* getMemoryManager () {
        return memoryManager;
    }

    void insert_process(Process* process) {
        if (getSchedulingAlgorithm() == enum_scheduling_algorithm::shortest_job) {
            if (ready_queue.size() == 0) {
                this->ready_queue.push_back(process);
            }
            else {
                Process* processoAux = new Process(1, std::numeric_limits<int>::max(), memoryManager);
                ready_queue.push_back(processoAux);
                for (int i = 0; i < ready_queue.size(); i++) {
                    if (ready_queue[i]->getTotalTime() > process->getTotalTime()) {
                        int j = ready_queue.size() - 1;
                        while (j > i) {
                            ready_queue[j] = ready_queue[j - 1];
                            j--;
                        }
                        ready_queue[i] = process;
                        break;
                    }
                }
            }
        }
        else {
            this->ready_queue.push_back(process);
        }
    }
    void schedule_process(Core* core, Process* process) {
        core->setCurrentProcess(process);
    }

    void deschedule_process(Core* core) {
        core->setCurrentProcess(NULL);
    }

    

    void fifo_scheduler() {
        removeAllFinishedProcessFromReadyQueue();
        for (Core* core : cpu->getCores()) {
            if (core->getCurrentProcess() == NULL) {
                if (getReadyQueue().size() > 0) {
                    getCpu()->getAnEmptyCore()->setCurrentProcess(getReadyQueue()[0]);
                    ready_queue.erase(ready_queue.begin());
                }
            }
        }
        decrementOneSecondEachProcess();
        //print_queue();
        //print_cores();
    }

    void decrementOneSecondEachProcess() {
        for (Core* core : cpu->getCores()) {
            if (core->getCurrentProcess() != NULL) {
                core->getCurrentProcess()->setReamainingTime(core->getCurrentProcess()->getReamainingTime() - 1);
                makeDynamicCall(core->getCurrentProcess());
            }  
        }
    }

    void makeDynamicCall(Process* process) {
        process->generate_random_dynamic_memory_call();
    }

    void removeAllFinishedProcessFromReadyQueue() {
        for (Core* core : cpu->getCores()) {
            if (core->getCurrentProcess() != NULL) {
                if (core->getCurrentProcess()->getReamainingTime() == 0) {
                    removeProcessById(core->getCurrentProcess()->getProcessId());
                    freeBlocksFromFinishedProcess(core->getCurrentProcess());
                    core->setCurrentProcess(NULL);
                }
            }
        }
    }

    void freeBlocksFromFinishedProcess(Process* process){
        for(MemoryBlock* memoryBlock : process->getMemoryPointers()){
            memoryManager->free(memoryBlock);
        }
    }

    void removeProcessById(int pId) {
        int id = 0;
        for (Process* process : ready_queue) {
            if (process->getProcessId() == pId) {
                ready_queue.erase (ready_queue.begin() + id);
            }
            id++;
        }
    }

    void shortest_job_first() {
        removeAllFinishedProcessFromReadyQueue();
        for (Core* core : cpu->getCores()) {
            if (core->getCurrentProcess() == NULL) {
                if (getReadyQueue().size() > 0) {
                    Process* shortestProcess = getShortestProcess();
                    getCpu()->getAnEmptyCore()->setCurrentProcess(shortestProcess);
                    removeProcessById(shortestProcess->getProcessId());
                }
            }
        }
        decrementOneSecondEachProcess();
        //print_queue();
        //print_cores();
    }

    Process* getShortestProcess() {
        Process* shortestProcess = ready_queue[0];
        for (Process* process : ready_queue) {
            if (process->getTotalTime() < shortestProcess->getTotalTime()) {
                shortestProcess = process;
            }
        }
        return shortestProcess;
    }

    void roundrobin() {
        removeAllFinishedProcessFromReadyQueue();
        putQuantumMaxedBackOnQueue();
        for (Core* core : cpu->getCores()) {
            if (core->getCurrentProcess() == NULL) {
                if (getReadyQueue().size() > 0) {
                    getCpu()->getAnEmptyCore()->setCurrentProcess(getReadyQueue()[0]);
                    ready_queue.erase(ready_queue.begin());
                }
            }
        }
        incrementQuantum();
        decrementOneSecondEachProcess();
        //print_queue();
        //print_cores();
    }

    void incrementQuantum() {
        for (Core* core : cpu->getCores()) {
            if (core->getCurrentProcess() != NULL) {
                core->getCurrentProcess()->setQuantumCount(core->getCurrentProcess()->getQuantumCount() + 1);
            }
        }
    }

    void putQuantumMaxedBackOnQueue() {
        for (Core* core : cpu->getCores()) {
            if (core->getCurrentProcess() != NULL) {
                if (core->getCurrentProcess()->getQuantumCount() >= dQuantum) {
                    core->getCurrentProcess()->setQuantumCount(0);
                    ready_queue.push_back(core->getCurrentProcess());
                    core->setCurrentProcess(NULL);
                }
            }
        }
    }

    void print_queue() {
        cout << "FILA: ----------" << endl;
        for (Process* process : ready_queue) {
            cout << "[Id: " << process->getProcessId() << " , Reamaining time: " <<  process->getReamainingTime() << ", total time: " << process->getTotalTime();;
            if (getSchedulingAlgorithm() == enum_scheduling_algorithm::round_robin) {
                cout << ", quantum: " << process->getQuantumCount() << "/" << dQuantum;
            }
            cout << "]";
            //<< endl;
        }
        cout << "----------" << endl;
    }

    void print_cores() {
        cout << "CORES: -------------------" << endl;
        int id = 0;
        for (Core* core : cpu->getCores()) {
            cout << "[Core ";
            cout << id;
            cout << ", Process:";
            if (core->getCurrentProcess() == NULL) {
                cout << "CORE_VAZIO]";
            } else {
                cout << "[id: " << core->getCurrentProcess()->getProcessId() << ", Reamaining time: " << core->getCurrentProcess()->getReamainingTime() << ", total time:" << core->getCurrentProcess()->getTotalTime();
                if (getSchedulingAlgorithm() == enum_scheduling_algorithm::round_robin) {
                    cout << ", quantum: " << core->getCurrentProcess()->getQuantumCount() << "/" << dQuantum;
                }
                cout << "], ";
            }
            id++;
            //cout << endl;
        }
        cout << "---------------" << endl << endl;
    }
};