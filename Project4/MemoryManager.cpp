#pragma once 
#include <vector>
#include "Enums.cpp"
#include <exception>
#include "MemoryBlock.cpp"

using namespace std;

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

    struct memory_excpetion : public exception {
        const char* exception() const throw () {
            return "Excecao Teste";
        }
    };

    MemoryBlock* malloc(int required_amount) {
        if (free_blocks_list == NULL) { // nao tem nenhum bloco livre
            return create_new_memory_block(required_Amount)
        } else
        if (required_amount <= available_memory) { // nao tem memoria pra criar bloco novo nem bloco livre
            try
            {
                throw memory_exception();
            }
            catch (memory_exception& e)
            {
                std::cout << "Sem memoria suficiente para criar um novo bloco" << std::endl;
                std::cout << e.exception() << std::endl;;
            }
        } else { // tem 1 ou mais blocos livres
            
        }
       
    }

    MemoryBlock* create_new_memory_block(int required_amount) {
        MemoryBlock* memory_block = new MemoryBlock(required_amount, memory->size(), NULL);
        this->memory.push_back(memory_block);
        return memory_block;
    }

    MemoryBlock* allocate_free_memory_block(MemoryBlock* pMemory_block) {
        if (pMemory_block == free_blocks_list) {
            free_blocks_list = pMemory_block->next_free_block;
        }
        else {
            MemoryBlock* aux = free_blocks_list;
            do {
                if (aux.next_free_block == pMemory_block) {
                    aux.next_free_block = pMemory_block.next_free_block;
                }
                aux = aux.next_free_block;
            } while (aux.next_free_block != pMemory_block);
        }
        
        return pMemory_block;
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
