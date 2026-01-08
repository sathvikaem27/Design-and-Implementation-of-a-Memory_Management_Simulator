#include "vm.h"
#include <iostream>
#include <queue>
#include <unordered_set>

using namespace std;

queue<int> vm_fifo;
unordered_set<int> memory;
int max_frames = 0;
int page_faults = 0;

void vm_init(int frames) {
    max_frames = frames;
    while (!vm_fifo.empty()) vm_fifo.pop();
    memory.clear();
    page_faults = 0;
    cout << "Virtual memory initialized\n";
}

void vm_access(int page) {
    if (memory.count(page)) {
        cout << "Page HIT\n";
    } else {
        cout << "Page FAULT\n";
        page_faults++;
        if ((int)memory.size() == max_frames) {
            int victim = vm_fifo.front();
            vm_fifo.pop();
            memory.erase(victim);
        }
        vm_fifo.push(page);
        memory.insert(page);
    }
}

void vm_stats() {
    cout << "Page Faults: " << page_faults << endl;
}
