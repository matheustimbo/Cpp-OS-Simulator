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
};
