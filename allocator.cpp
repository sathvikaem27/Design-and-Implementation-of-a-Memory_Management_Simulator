#include "allocator.h"
#include <iostream>
#include <climits>

using namespace std;

Block* head = nullptr;
int memory_size = 0;
int next_id = 1;
string allocator_type = "first_fit";

void init_memory(int size) {
    memory_size = size;
    next_id = 1;

    head = new Block{0, size, true, -1, nullptr};
}

void set_allocator(const string& type) {
    allocator_type = type;
}

Block* first_fit(int size) {
    Block* curr = head;
    while (curr) {
        if (curr->free && curr->size >= size)
            return curr;
        curr = curr->next;
    }
    return nullptr;
}

Block* best_fit(int size) {
    Block* curr = head;
    Block* best = nullptr;
    int min_diff = INT_MAX;

    while (curr) {
        if (curr->free && curr->size >= size) {
            int diff = curr->size - size;
            if (diff < min_diff) {
                min_diff = diff;
                best = curr;
            }
        }
        curr = curr->next;
    }
    return best;
}

Block* worst_fit(int size) {
    Block* curr = head;
    Block* worst = nullptr;
    int max_size = -1;

    while (curr) {
        if (curr->free && curr->size >= size && curr->size > max_size) {
            max_size = curr->size;
            worst = curr;
        }
        curr = curr->next;
    }
    return worst;
}

void* mem_malloc(int size) {
    Block* block = nullptr;

    if (allocator_type == "first_fit")
        block = first_fit(size);
    else if (allocator_type == "best_fit")
        block = best_fit(size);
    else if (allocator_type == "worst_fit")
        block = worst_fit(size);

    if (!block) {
        cout << "Allocation failed\n";
        return nullptr;
    }

    if (block->size > size) {
        Block* new_block = new Block{
            block->start + size,
            block->size - size,
            true,
            -1,
            block->next
        };
        block->next = new_block;
        block->size = size;
    }

    block->free = false;
    block->id = next_id++;

    cout << "Allocated block id=" << block->id
         << " at address=" << block->start << endl;

    return (void*)block->start;
}

void mem_free(int id) {
    Block* curr = head;

    while (curr) {
        if (!curr->free && curr->id == id) {
            curr->free = true;
            curr->id = -1;

            // Coalescing
            while (curr->next && curr->next->free) {
                curr->size += curr->next->size;
                curr->next = curr->next->next;
            }

            cout << "Block " << id << " freed and merged\n";
            return;
        }
        curr = curr->next;
    }

    cout << "Invalid block id\n";
}

void dump_memory() {
    Block* curr = head;
    while (curr) {
        cout << "[" << curr->start << " - "
             << curr->start + curr->size - 1 << "] ";

        if (curr->free)
            cout << "FREE\n";
        else
            cout << "USED (id=" << curr->id << ")\n";

        curr = curr->next;
    }
}

void print_stats() {
    Block* curr = head;
    int used = 0, free_mem = 0, largest_free = 0;

    while (curr) {
        if (curr->free) {
            free_mem += curr->size;
            if (curr->size > largest_free)
                largest_free = curr->size;
        } else {
            used += curr->size;
        }
        curr = curr->next;
    }

    cout << "Total memory: " << memory_size << endl;
    cout << "Used memory: " << used << endl;
    cout << "Free memory: " << free_mem << endl;

    if (free_mem > 0) {
        double ext_frag = 100.0 * (1.0 - (double)largest_free / free_mem);
        cout << "External fragmentation: " << ext_frag << "%\n";
    }
}
