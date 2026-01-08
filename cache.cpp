#include "cache.h"
#include <iostream>
#include <queue>
#include <unordered_set>

using namespace std;

queue<int> cache_fifo;

unordered_set<int> cache;
int cache_size = 0;
int hits = 0, misses = 0;

void cache_init(int size) {
    cache_size = size;
    while (!cache_fifo.empty()) cache_fifo.pop();
    cache.clear();
    hits = misses = 0;
    cout << "L1 Cache initialized (FIFO)\n";
}

void cache_access(int address) {
    if (cache.count(address)) {
        hits++;
        cout << "Cache HIT\n";
    } else {
        misses++;
        cout << "Cache MISS\n";
        if ((int)cache.size() == cache_size) {
            int evict = cache_fifo.front();
            cache_fifo.pop();
            cache.erase(evict);
        }
        cache_fifo.push(address);
        cache.insert(address);
    }
}

void cache_stats() {
    cout << "Cache Hits: " << hits << endl;
    cout << "Cache Misses: " << misses << endl;
}
