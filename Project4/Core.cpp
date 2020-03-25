#pragma once 
#include "Process.cpp"
class Core {
    Process* current_process;
public:
    Core() {
    }

    Process* getCurrentProcess() {
        return current_process;
    }

    void setCurrentProcess(Process* currentProcess) {
        current_process = currentProcess;
    }
};
