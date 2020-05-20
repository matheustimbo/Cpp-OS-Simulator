#pragma once 
class MemoryBlock {
private:
    int occupied_size;
    int total_block_size;
    int block_address;
    int next_free_block;
public:

    MemoryBlock() {
    }
};
