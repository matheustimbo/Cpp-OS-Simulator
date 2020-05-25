#pragma once 
#include <vector>
#include "Enums.cpp"
#include "MemoryBlock.cpp"
class MemoryManager {
private:
    int total_memory;
    int memory_overhead;
    int available_memory;
    int occupied_memory;
    int number_quick_lists;
    int minimum_amount_calls;

    vector<MemoryBlock*> memory;
    MemoryBlock* free_blocks_list;
    vector<MemoryBlock*> quick_fit_free_blocks;
public:

    MemoryManager(int p_total_memory) {
        total_memory = p_total_memory;
        free_blocks_list = NULL;
    }

    MemoryBlock* malloc(int required_amount) {
        if (free_blocks_list == NULL) { // nao tem nenhum bloco livre
            MemoryBlock* memory_block = new MemoryBlock(required_amount, memory->size(), NULL)
                return memory_block
        } else
        if (required_amount <= available_memory) { // nao tem memoria pra criar bloco novo nem bloco livre

        } else { // tem 1 ou mais blocos livres
            MemoryBlock* aux = free_blocks_list;
            while (aux != NULL) {

                aux = aux->next_free_block;
            }
        }
       
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
