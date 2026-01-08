#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <string>

struct Block {
    int start;
    int size;
    bool free;
    int id;
    Block* next;
};

void init_memory(int size);
void set_allocator(const std::string& type);
void* mem_malloc(int size);
void mem_free(int id);
void dump_memory();
void print_stats();

#endif
