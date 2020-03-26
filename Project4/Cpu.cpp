#pragma once 
#include <vector>
#include "Core.cpp"

using namespace std;

class Cpu {
    vector<Core*> cores;
public:
    Cpu(int core_number) {

        for (int i = 0; i < core_number; i++) {
            cores.push_back(new Core());
        }
    }

    vector<Core*> getCores() {
        return cores;
    }

    int get_num_empty_cores() {
        int coresAvailable = 0;
        for (int i = 0; i < getCores().size(); i++) {
            if (getCores()[i]->getCurrentProcess() == NULL) {
                coresAvailable++;
            }
        }
        return coresAvailable;
    }

    Core* getAnEmptyCore() {
        if (get_num_empty_cores() == 0) {
            return NULL;
        }
        for (int i = 0; i < getCores().size(); i++) {
            if (getCores()[i]->getCurrentProcess() == NULL) {
                return getCores()[i];
            }
        }
    }
};
