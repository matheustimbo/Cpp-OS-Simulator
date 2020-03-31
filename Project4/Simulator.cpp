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

    enum_scheduling_algorithm scheduling_algorithm;

    Simulator(int core_number, int dquantum, enum_scheduling_algorithm pScheduling_algorithm) {
        kernel = new Kernel(core_number, dquantum, pScheduling_algorithm);
        processor_cores_number = core_number;
        quantum = dquantum;
        scheduling_algorithm = pScheduling_algorithm;
        id_count = 0;
    }

    void batch_process_init(int number_of_process) {
        for (int i = 0; i < number_of_process; i++) {
            create_random_process();
        }
    }

    void create_random_process() {
        kernel->create_process(id_count, (rand() % 21)+1);
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
        batch_process_init(15);
        thread kernelThread(&Kernel::run, getKernel());
        kernelThread.join();
    }
};

void teste(Simulator* simulator) {
    int seconds = 0;
    while (true) {
        //cout << "thread simulator segundo t[" << seconds << "]" << endl;
        seconds++;
        simulator->create_random_process();
        //simulator->create_random_process();
        //simulator->getKernel()->getScheduler()->print_queue();
        //simulator->getKernel()->getScheduler()->print_cores();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    Simulator* simulator = new Simulator(11, 10, enum_scheduling_algorithm::shortest_job);
    thread simulatorThread(teste, simulator);
    simulator->run();
    simulatorThread.join();
}
