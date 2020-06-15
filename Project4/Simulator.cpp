#pragma once 
#include <string>
#include <iostream>
#include <thread>
#include "Enums.cpp"
#include "Kernel.cpp"

using namespace std;


class Simulator {
private:
    Kernel* kernel;
    int processor_cores_number;

    int quantum;

    int id_count;

    void batch_process_init() {

    }

public:


    Simulator(int core_number, int dquantum, enum_scheduling_algorithm pScheduling_algorithm, enum_memory_allocation_algorithm pMemoryAllocationAlgorithm, int pTotal_installed_memory, int number_quick_lists, int number_memory_calls) {
        kernel = new Kernel(core_number, dquantum, pScheduling_algorithm, pMemoryAllocationAlgorithm, pTotal_installed_memory);
        processor_cores_number = core_number;
        quantum = dquantum;
        id_count = 0;
    }

    void batch_process_init(int number_of_process) {
        for (int i = 0; i < number_of_process; i++) {
            create_random_process();
        }
    }

    void create_random_process() {
        kernel->create_process(id_count, (rand() % 21) + 1);
        id_count++;
    }

    Kernel* getKernel() {
        return kernel;
    }

    int getIdCount() {
        return id_count;
    }

    void setIdCount(int id) {
        id_count = id;
    }

    void run() {
        batch_process_init(5);
        thread kernelThread(&Kernel::run, getKernel());
        kernelThread.join();
    }
};

void teste(Simulator* simulator) {
    int seconds = 0;
    while (true) {
        //cout << "thread simulator segundo t[" << seconds << "]" << endl;
        seconds++;
        if (seconds % 5 == 0) {
            simulator->create_random_process();
        }
        //simulator->create_random_process();
        //simulator->getKernel()->getScheduler()->print_queue();
        //simulator->getKernel()->getScheduler()->print_cores();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    Simulator* simulator = new Simulator(1, 4, enum_scheduling_algorithm::shortest_job, enum_memory_allocation_algorithm::first_fit, 8192, 1, 1);
    thread simulatorThread(teste, simulator);
    simulator->run();
    simulatorThread.join();
}
