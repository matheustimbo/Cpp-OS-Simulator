#pragma once 
#include <vector>
#include "Enums.cpp"
#include <exception>
#include <thread>
#include "MemoryBlock.cpp"

using namespace std;

class MemoryManager {
private:


    MemoryBlock* head;
    MemoryBlock* tail;

    enum_memory_allocation_algorithm memory_allocation_algorithm;

    vector<MemoryBlock*> memory;
    MemoryBlock* free_blocks_list;
    vector<MemoryBlock*> quick_fit_free_blocks;
public:
    int total_memory;   //toda a memoria do sistema
    int memory_overhead; //soma da memoria dos blocos
    int available_memory; //soma da memoria dos blocos livres
    int occupied_memory; //soma da memoria dos blocos ocupados
    int memoria_nao_alocada; //total_memory - memoryoverhead = memoria disponivel pra criar blocos
    int number_quick_lists;
    int minimum_amount_calls;

    MemoryManager(int p_total_memory, enum_memory_allocation_algorithm pMemory_allocation_algorithm) {
        memory_allocation_algorithm = pMemory_allocation_algorithm;
        total_memory = p_total_memory;
        memory_overhead = 0;
        available_memory = 0;
        occupied_memory = 0;
        memoria_nao_alocada = p_total_memory;
        free_blocks_list = NULL;
        head = NULL;
        tail = NULL;
    }

    vector<MemoryBlock*> getMemory() {
        return memory;
    }

    void run() {
        thread memoryManagerThread(&MemoryManager::runMemoryManagerAlgorithm, this);
        memoryManagerThread.join();
    }

    void runMemoryManagerAlgorithm() {
        cout<<"AAAAAAA"<<endl;
        int seconds = 0;

        while (true) {

        }
    }

    void add_list(MemoryBlock* tmp) {
        if (head == NULL) {
            head = tmp;
            tail = tmp;
        }
        else {
            tail->next_free_block = tmp;
            tail = tail->next_free_block;
        }
    }

    void delete_list(MemoryBlock* tmp) {
        MemoryBlock* deletePointer = NULL; 
        tail->next_free_block = tmp;
        tail = tail->next_free_block;

        while (tail != NULL && tail->next_free_block != tmp) {
            tail->next_free_block = tmp;
            tail = tail->next_free_block;
        }

        if (tail == NULL) {
            cout << tmp << "Nao esta na lista";
            delete deletePointer;
        }
        else {
            deletePointer = tail;
            tail = tail->next_free_block;
            tail->next_free_block = tmp;
            delete deletePointer;
            cout << " O valor " << tmp << " foi deletado";
        }
    }

    struct memory_exception : public exception {
        const char* exception() const throw () {
            return "Excecao Teste";
        }
    };

    MemoryBlock* malloc(int required_amount) {
        cout<<"entrou no malloc"<<endl;
        cout<<"required amount " << required_amount << endl;
        if (this->free_blocks_list == NULL) { // nao tem nenhum bloco livre
            cout<<"free blocks list ta null "<<endl;
            return create_new_memory_block(required_amount);
        } else {
            cout<<"free blocks list não ta null, então" <<endl;
            if (required_amount >= memoria_nao_alocada) { // nao tem memoria pra criar bloco novo nem bloco livre
                cout<<"nao tem memoria suficiente"<<endl;
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
                cout<<"tem memoria suficiente, vamo chaamr um metodo de alocação" <<endl;
                switch (this->memory_allocation_algorithm)
                {
                    case enum_memory_allocation_algorithm::first_fit:
                        cout<<"c"<<endl;
                        return this->first_fit(required_amount);
                        break;

                    case enum_memory_allocation_algorithm::best_fit:
                        cout<<"d"<<endl;
                        return this->best_fit(required_amount);
                        break;

                    case enum_memory_allocation_algorithm::quick_fit:
                        cout<<"e"<<endl;
                        return this->quick_fit();
                        break;
                    default:
                        return this->first_fit(required_amount);
                }
            }
        }
    }

    MemoryBlock* create_new_memory_block(int required_amount) {
        cout<<"criar novo bloco"<<endl;
        MemoryBlock* memory_block = new MemoryBlock(required_amount, this->memory.size());
        this->memory.push_back(memory_block);
        memory_overhead += required_amount;
        occupied_memory += required_amount;
        memoria_nao_alocada = total_memory - memory_overhead;
        cout<<"vai retornar um bloco de tamanho "<< memory_block->total_block_size <<endl;
        return memory_block;
    }
        /*if((free_blocks_list == NULL){)
            free_blocks_list = memory_block;
        } else{
            MemoryBlock* aux = free_blocks_list;
            do {

                if (aux->next_free_block == NULL) {
                    aux->next_free_block = memory_block;
                }
                else {
                    aux = aux->next_free_block;
                }
            } while (aux->next_free_block != NULL);
        }*/


        //this->memory_overhead = this->memory_overhead + required_amount;
        //this->available_memory = this->available_memory + required_amount;




    MemoryBlock* allocate_free_memory_block(MemoryBlock* pMemory_block) {//tira um bloco da lista de blocos free
        cout << "alocar bloco de memoria" <<endl;
        if (pMemory_block == free_blocks_list) {
            cout<<"aaa"<<endl;
            free_blocks_list = pMemory_block->next_free_block; //se ele for o primeiro da lista
        }
        else {
            cout<<"bbb"<<endl;
            MemoryBlock* aux = free_blocks_list;
            do {
                if (aux->next_free_block == pMemory_block) {
                    aux->next_free_block = pMemory_block->next_free_block;
                }
                aux = aux->next_free_block;
            } while (aux->next_free_block != pMemory_block);
        }
        this->available_memory = this->available_memory - pMemory_block->total_block_size;
        this->occupied_memory = this->occupied_memory + pMemory_block->total_block_size;
        return pMemory_block;
        
    }

    void free(MemoryBlock* memoryToFree) {
        if(this->free_blocks_list == NULL){
            this->free_blocks_list = memoryToFree;
        }
        else {
            MemoryBlock* aux = free_blocks_list;
            do {
                if (aux->next_free_block == NULL) {
                    aux->next_free_block = memoryToFree;
                }
                else {
                    aux = aux->next_free_block;
                }
            } while (aux->next_free_block != NULL);
        }
        this->available_memory = this->available_memory + memoryToFree->total_block_size;
        this->occupied_memory = this->occupied_memory - memoryToFree->total_block_size;
    }

    void set_allocation_algorithm(enum_memory_allocation_algorithm pMemoryAllocationAlgorithm) {
        memory_allocation_algorithm = pMemoryAllocationAlgorithm;
    }

    bool check_free_memory(int required_amount) {
        MemoryBlock* aux = this->free_blocks_list;
        do {
            if (aux->total_block_size >= required_amount) {
                return true;
                break;
            }
            aux = aux->next_free_block;
        } while (aux->next_free_block != NULL);
        return false;
    }

    MemoryBlock* first_fit(int required_amount) {
        cout<<"entrou no first_fit"<<endl;
        MemoryBlock* firstFit = NULL;

        if(this->free_blocks_list != NULL){
            MemoryBlock* aux = this->free_blocks_list;
            do {
                cout<<"bb1"<<endl;
                if (aux->total_block_size >= required_amount) {
                    cout << "deu fit" << endl;
                    firstFit = aux;
                    break;
                }
                aux = aux->next_free_block;
            } while (aux != NULL);
        }

        if (firstFit == NULL) {
            //criar bloco de memoria novo
            cout<<"bb2"<<endl;
            return create_new_memory_block(required_amount);
        }
        else {
            allocate_free_memory_block(firstFit);
            return firstFit;
        }
    }

    MemoryBlock* best_fit(int required_amount) {
        MemoryBlock* bestMemoryBlockThatFits = NULL;
        MemoryBlock* aux = free_blocks_list;
        do {
            if (aux->total_block_size >= required_amount) {
                if (bestMemoryBlockThatFits != NULL) {
                    bestMemoryBlockThatFits = aux;
                }
                else {
                    if (aux->total_block_size < bestMemoryBlockThatFits->total_block_size)
                        bestMemoryBlockThatFits = aux;
                }
            }
            aux = aux->next_free_block;
        } while (aux->next_free_block != NULL);

        if (bestMemoryBlockThatFits == NULL) {
            //criar bloco de memoria novo
            return create_new_memory_block(required_amount);
        }
        else {
            allocate_free_memory_block(bestMemoryBlockThatFits);
            return bestMemoryBlockThatFits;
        }
    }

    MemoryBlock* quick_fit() {

    }
};
