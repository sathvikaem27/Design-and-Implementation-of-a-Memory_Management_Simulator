# Memory Management Simulator

## Overview
This project implements a user-space simulator for core operating system
memory-management concepts including dynamic allocation, caching, and
virtual memory.

## Features
- Physical memory simulation
- First Fit, Best Fit, Worst Fit allocation
- Block splitting and coalescing
- Memory dump and fragmentation statistics

## Optional Extensions
- Buddy Memory Allocation
- L1 Cache Simulation (FIFO)
- Virtual Memory Paging (FIFO)

## Compilation
```bash
g++ main.cpp allocator.cpp buddy.cpp cache.cpp vm.cpp -o memsim
## Execution
./memsim
## Sample Commands
init memory 1024
set allocator first_fit
malloc 100
malloc 200
free 1
dump
stats

buddy_init 1024
buddy_malloc 100
buddy_dump

cache_init 3
cache_access 10
cache_stats

vm_init 3
vm_access 1
vm_stats
