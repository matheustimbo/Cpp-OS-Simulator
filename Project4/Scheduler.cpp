#pragma once 
#include <vector>
#include <thread>
#include "Core.cpp"
#include "Enums.cpp"
#include "Cpu.cpp"

using namespace std;


class Scheduler {
    vector<Process*> ready_queue;
    enum_scheduling_algorithm scheduling_algorithm;
    int dQuantum;
    
public:
    Cpu* cpu;

    Scheduler(enum_scheduling_algorithm schedulingAlgorithm, int pDQuantum, int core_number) {
        scheduling_algorithm = schedulingAlgorithm;
        dQuantum = pDQuantum;
        cpu = new Cpu(core_number);
    }

    Cpu* getCpu() {
        return cpu;
    }

    vector<Process*> getReadyQueue() {
        return ready_queue;
    }

    void setReadyQueue(vector<Process*> readyQueue) {
        ready_queue = readyQueue;
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
        if (getSchedulingAlgorithm() == enum_scheduling_algorithm::fifo) {
            fifo_scheduler();
        }
        if (getSchedulingAlgorithm() == enum_scheduling_algorithm::round_robin) {
            shortest_job_first();
        }
        if(getSchedulingAlgorithm() == enum_scheduling_algorithm::shortest_job) {
            roundrobin();
        }
    }

    void run() {
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            thread scheduleThread(&Scheduler::runSchedulingAlgorithm, this);

            //scheduleThread.join();
        }
    }

    void insert_process(Process* process) {
        this->ready_queue.push_back(process);
    }

    void schedule_process(Core* core, Process* process) {
        core->setCurrentProcess(process);
    }

    void deschedule_process(Core* core) {
        core->setCurrentProcess(NULL);
    }

    int get_num_empty_cores() {
        int coresAvailable = 0;
        for (int i = 0; i < getCpu()->getCores().size(); i++) {
            if (getCpu()->getCores()[i]->getCurrentProcess() != NULL) {
                coresAvailable++;
            }
        }
        return coresAvailable;
    }

    void fifo_scheduler() {
        cout << "Numero de cores vazios" << endl;
        cout << get_num_empty_cores() << endl;
    }

    void shortest_job_first() {

    }

    void roundrobin() {

    }

    void print_queue() {
        cout << "FILA: ";
        for (int i = 0; i < ready_queue.size(); i++) {
            cout << "[ID: ";
            cout << ready_queue[i]->getProcessId();
            cout << " , TIME: ";
            cout << ready_queue[i]->getReamainingTime();
            cout << "], ";
        }
        cout << "" << endl;
    }

    void print_cores() {
        cout << "CORES: ";
        for (int i = 0; i < getCpu()->getCores().size(); i++) {
            cout << "[COREID: ";
            cout << i;
            cout << ", ";
            if (getCpu()->getCores()[i]->getCurrentProcess() == NULL) {
                cout << "CORE_VAZIO]";
            }
            else {
                cout << "[ID: ";
                cout << getCpu()->getCores()[i]->getCurrentProcess()->getProcessId();
                cout << " , TIME: ";
                cout << getCpu()->getCores()[i]->getCurrentProcess()->getReamainingTime();
                cout << "], ";
            }
            
        }
        cout << "" << endl;
    }
};