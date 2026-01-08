#ifndef BUDDY_H
#define BUDDY_H

void buddy_init(int size);
void buddy_malloc(int size);
void buddy_free(int address);
void buddy_dump();

#endif
