#pragma once 
#include <vector>
#include "Enums.cpp"
class MemoryManager {
private:
    int total_memory;
    int memory_overhead;
    int available_memory;
    int occupied_memory;
    int number_quick_lists;
    int minimum_amount_calls;

    vector<MemoryBlock*> memory;
    vector <MemoryBlock*> free_blocks_list  //COLOCAR COMO PONTIERO
        vector<MemoryBlock*> quick_fit_free_blocks;
public:

    MemoryManager(int pTotal_memory) {
    }

    void malloc() {

    }

    void free() {

    }

    void set_allocation_algorithm(enum_memory_allocation_algorithm pMemoryAllocationAlgorithm) {

    }

    void check_free_memory() {

    }

    void first_fit() {

    }

    void best_fit() {

    }

    void quick_fit() {

    }
};
