#pragma once 
class MemoryBlock {
   
public:
    int occupied_size;
    int total_block_size;
    int block_address;
    MemoryBlock* next_free_block;

    MemoryBlock(int p_total_block_size, int p_block_address, MemoryBlock* p_next_free_block) {
        total_block_size = p_total_block_size;
        block_address = p_block_address;
        next_free_block = p_next_free_block;
        occupied_size = p_total_block_size;
    }

};
