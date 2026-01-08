#include <iostream>
#include <sstream>
#include "allocator.h"
#include "buddy.h"
#include "cache.h"
#include "vm.h"



using namespace std;

int main() {
    string line;

    cout << "Memory Management Simulator\n";

    while (true) {
        cout << "> ";
        getline(cin, line);
        stringstream ss(line);
        string cmd;
        ss >> cmd;

        if (cmd == "init") {
            string temp;
            int size;
            ss >> temp >> size;
            init_memory(size);
        }
        else if (cmd == "set") {
            string temp, type;
            ss >> temp >> type;
            set_allocator(type);
        }
        else if (cmd == "malloc") {
            int size;
            ss >> size;
            mem_malloc(size);
        }
        else if (cmd == "free") {
            int id;
            ss >> id;
            mem_free(id);
        }
        else if (cmd == "dump") {
            dump_memory();
        }
        else if (cmd == "stats") {
            print_stats();
        }
        else if (cmd == "exit") {
            break;
        }
        else if (cmd == "buddy_init") {
        int size; ss >> size;
         buddy_init(size);
       }
       else if (cmd == "buddy_malloc") {
        int size; ss >> size;
       buddy_malloc(size);
      }
      else if (cmd == "buddy_free") {
      int addr; ss >> addr;
      buddy_free(addr);
      }
      else if (cmd == "buddy_dump") {
      buddy_dump();
      }
      else if (cmd == "cache_init") {
      int size;
      ss >> size;
      cache_init(size);
     }
     else if (cmd == "cache_access") {
     int addr;
     ss >> addr;
     cache_access(addr);
     }
     else if (cmd == "cache_stats") {
     cache_stats();
     }
     else if (cmd == "vm_init") {
    int frames;
    ss >> frames;
    vm_init(frames);
    }
    else if (cmd == "vm_access") {
    int page;
    ss >> page;
    vm_access(page);
    }
    else if (cmd == "vm_stats") {
    vm_stats();
    }


    else {
            cout << "Unknown command\n";
     }
    }
    return 0;
}
