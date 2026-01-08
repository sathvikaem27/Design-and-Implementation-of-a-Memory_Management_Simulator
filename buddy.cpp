#include "buddy.h"
#include <iostream>
#include <map>
#include <vector>
#include <cmath>

using namespace std;

map<int, vector<int>> free_lists;
int buddy_memory_size;

int next_power_of_two(int n) {
    int p = 1;
    while (p < n) p <<= 1;
    return p;
}

void buddy_init(int size) {
    buddy_memory_size = size;
    free_lists.clear();
    free_lists[size].push_back(0);
    cout << "Buddy system initialized with size " << size << endl;
}

void buddy_malloc(int size) {
    int req = next_power_of_two(size);

    for (auto& entry : free_lists) {
        int block_size = entry.first;
        auto& blocks = entry.second;

        if (block_size >= req && !blocks.empty()) {
            int addr = blocks.back();
            blocks.pop_back();

            while (block_size > req) {
                block_size /= 2;
                free_lists[block_size].push_back(addr + block_size);
            }

            cout << "Buddy allocated at address " << addr
                 << " with size " << req << endl;
            return;
        }
    }
    cout << "Buddy allocation failed\n";
}


void buddy_free(int address) {
    free_lists[buddy_memory_size].push_back(address);
    cout << "Buddy block freed at address " << address << endl;
}

void buddy_dump() {
    cout << "Buddy Free Lists:\n";
    for (auto& entry : free_lists) {
        int size = entry.first;
        auto& blocks = entry.second;

        cout << "Size " << size << ": ";
        for (int addr : blocks)
            cout << addr << " ";
        cout << endl;
    }
}

