//
// Created by leon on 18.10.15.
//

#ifndef SPZ1_LISTOFBLOCK_H
#define SPZ1_LISTOFBLOCK_H


#include <stddef.h>

class ListOfBlock {
private:
       char *mem;
       size_t len;
public:ListOfBlock(size_t size);
       ~ListOfBlock();
       void* CreateBlock(size_t size);
       void* DeleteBlock(void *addr);
       bool IsBusy(void* addr);
       void* GetNext(void *addr);
       void* GetPrevious(void *addr);
       void* GetFirst();
       void* ChangeSizeOrCreateNew(void *addr,size_t NewSize);
       void* GetLastAdress();
};


#endif //SPZ1_LISTOFBLOCK_H
