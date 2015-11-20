//
// Created by leon on 18.10.15.
//

#include "Allocator.h"
#include <iostream>


Allocator::Allocator(size_t size)
{
listOfBlock=new ListOfBlock(size);
};
void* Allocator::mem_alloc(size_t size)
{
return listOfBlock->CreateBlock(size);
}
void Allocator::mem_free(void *addr)
{
    listOfBlock->DeleteBlock(addr);
}
void* Allocator::mem_realloc(void *addr, size_t size)
{
if(addr==NULL) return this->mem_alloc(size);
return listOfBlock->ChangeSizeOrCreateNew(addr,size);
}

void Allocator::mem_dump()
{
    TypeOfMemoryDump t=TextDump;
    mem_dump(t);
}

void Allocator::mem_dump(TypeOfMemoryDump type)
{
    if(type==TextDump)
    {
        std::cout<<"Text dump of memory"<<std::endl;
        void* element=listOfBlock->GetFirst();
        int number=1;
        while(element!=NULL)
        {
            std::cout<<"block number:"<<number<<std::endl;
            if(listOfBlock->IsBusy(element))
                std::cout<<"Block is busy, ";
            else
                std::cout<<"Block is free, ";
            std::cout<<"size: "<<*(int*) element;
            std::cout<<", previous block size: "<<*(int*) (element+sizeof(int))<<std::endl;
            element=listOfBlock->GetNext(element);
            number++;
        }
    }
    else if(type==GlobalDumpInInt)
    {
        void* element=listOfBlock->GetFirst();
        while(element<listOfBlock->GetLastAdress())
        {
            std::cout<<*(int*)element<<" ";
            element+=sizeof(int);
        }

    }
}
