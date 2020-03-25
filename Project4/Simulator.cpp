#pragma once 
#include <string>
#include <iostream>
#include <thread>
#include "Enums.cpp"
#include "Kernel.cpp"

using namespace std;


class Simulator {
    Kernel* kernel;
    int processor_cores_number;

    int quantum;

    int id_count;

    void batch_process_init() {

    }

    void run() {
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
        kernel->create_process(id_count, rand() % 21);
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


};

void teste(Simulator* simulator) {
    simulator->getKernel()->getScheduler()->print_queue();
    simulator->getKernel()->getScheduler()->print_cores();
}

int main() {
    vector<Core*>* cores = new vector<Core*>;
    Simulator* simulator = new Simulator(4, 10, enum_scheduling_algorithm::fifo);

    simulator->batch_process_init(5);
    simulator->getKernel()->run();
    
    int seconds = 0;

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        seconds = seconds + 1;
        cout << "T[";
        cout << seconds;
        cout << "]: ";
        thread teste1(teste, simulator);
        
        teste1.join();
    }
}
