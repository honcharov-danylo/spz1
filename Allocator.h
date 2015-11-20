//
// Created by leon on 18.10.15.
//

#ifndef SPZ1_ALLOCATOR_H
#define SPZ1_ALLOCATOR_H

#include <stddef.h>
#include "ListOfBlock.h"


enum TypeOfMemoryDump
{
    GlobalDumpInInt,
    TextDump
};

class Allocator {
private:
   // size_t memory;
    ListOfBlock *listOfBlock;
public: Allocator(size_t size);
    void *mem_alloc(size_t size);
    void *mem_realloc(void *addr, size_t size);
    void mem_free(void *addr);
    void mem_dump(TypeOfMemoryDump type);
    void mem_dump();
};


#endif //SPZ1_ALLOCATOR_H
