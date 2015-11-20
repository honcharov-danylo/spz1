//
// Created by leon on 18.10.15.
//

#include <iostream>
#include "ListOfBlock.h"

ListOfBlock::ListOfBlock(size_t size)
{
    if(size%4!=0)
        size=size+(4-size%4);
    len=size;
    mem=new char[size];
    *(int *) mem = size - sizeof(int) * 3;
    *(int *) (mem + sizeof(int)) = 0;
    *(int *) (mem + sizeof(int) * 2) = 0;
}
ListOfBlock::~ListOfBlock()
{
    delete mem;
}
void* ListOfBlock::GetNext(void *addr)
{
    int s=*(int*)addr;
    if(addr+s+sizeof(int)*3<GetLastAdress())
        return ( addr+s+sizeof(int)*3);
    else return NULL;
}

void* ListOfBlock::GetPrevious(void *addr)
{
    int s=*(int*)(addr+sizeof(int));
    if(s!=0)
        return ( addr-s);//-sizeof(int)*1); //*3?
    else return NULL;
}
bool ListOfBlock::IsBusy(void *addr)
{
    if(*(int*) (addr+sizeof(int)*2)==0)
        return false;
    else return true;
}
void* ListOfBlock::CreateBlock(size_t size)
{
char* element=mem;
    if(size<sizeof(int)*3)
        return NULL;
    if(size%4!=0)
        size=size+(4-size%4);
while(element<GetLastAdress())
{
    if((!IsBusy(element)) && (*(int*)element>size))
    {
        if((*(int*)element>size+4*sizeof(int)))
        {
            int initialsize=*(int*)element;
            int initialback=*(int*)(element+sizeof(int));
            *(int *) element = size - sizeof(int) * 3;
            *(int *) (element + sizeof(int) * 2) = 1;

            *(int *)(element+size)=initialsize-size;
            *(int *)(element+size+sizeof(int))=size;
            *(int *)(element+size+sizeof(int)*2)=0;
            return element;
        }
        else
        {

            int initialback=*(int*)(element+sizeof(int));
            size=*(int*)element;
            *(int *) element = size - sizeof(int) * 3;
            *(int *) (element + sizeof(int) * 2) = 1;
            return element;
        }
    }
    else
    {
        element=(char*)GetNext(element);
    }

}
return NULL;
}

void* ListOfBlock::DeleteBlock(void *addr)
{
    void* previous_block=GetPrevious(addr);
    void* next_block=GetNext(addr);
    *(int *) (addr+sizeof(int)*2)=0;
    if(previous_block!=NULL && !IsBusy(previous_block)) {
        int dopsize = sizeof(int) * 3;
       // std::cout<<*(int *) previous_block<<std::endl;
        *(int *) previous_block = *(int *) previous_block + *(int *) addr;
        *(int *) previous_block=*(int *) previous_block+dopsize;
        *(int *) addr=0;
        *(int *) (addr+sizeof(int))=0;
     if(next_block!=NULL) {
         *(int *) (next_block + sizeof(int)) = *(int *) previous_block;

         *(int *) (next_block + sizeof(int)) = *(int *) (next_block + sizeof(int)) + dopsize;
     }
    }
    if(next_block!=NULL && !IsBusy(next_block))
    {
        DeleteBlock(next_block);
    }
    return NULL;
}
void* ListOfBlock::ChangeSizeOrCreateNew(void *addr, size_t NewSize)
{

    if(NewSize%4!=0)
        NewSize=NewSize+(4-NewSize%4);

    int oldSize = *(int *) (addr);

    if(NewSize<3*sizeof(int)) return NULL;

    if(*(int *)(addr)+sizeof(int)*3>NewSize) {
        if (oldSize>=NewSize + 1 * sizeof(int)) {
            *(int *) (addr) = NewSize-3*sizeof(int);
            void *nb = (addr + NewSize);//+3*sizeof(int));
            *(int *) nb = oldSize-NewSize;///3*sizeof(int);
            std::cout<<*(int *)nb<<std::endl;
            *(int *) (nb+sizeof(int))=NewSize;
            *(int *)(nb+2*sizeof(int))=0;
            if(GetNext(nb)!=NULL)
            {
                *(int *)(GetNext(nb)+sizeof(int))=(*(int *)nb+3*sizeof(int));
            }
            return addr;
        }
        else
        {

            if(GetNext(addr)!=NULL && !IsBusy(GetNext(addr)))
            {
                int oldsizenextBlock=*(int *)GetNext(addr);
                *(int *)GetNext(addr)=0;
                *(int *)(GetNext(addr)+sizeof(int))=0;
                *(int *)(GetNext(addr)+sizeof(int)*2)=0;

                *(int *) addr=NewSize-3*sizeof(int);
                void* nb=(addr+NewSize);
                *(int *) nb=oldsizenextBlock+(oldSize-NewSize);
                *(int *)(nb+sizeof(int))=NewSize;
                *(int *)(nb+sizeof(int)*2)=0;
            }
            else {
                return addr;
            }
        }
    }
    else
    {
        if(GetNext(addr)!=NULL && !IsBusy(GetNext(addr)) && *(int *)(GetNext(addr))+oldSize>NewSize)
        {
            if(*(int *)(GetNext(addr))+oldSize>NewSize+1*sizeof(int))
            {

                int oldsizeNextBlock;
                oldsizeNextBlock=*(int *)GetNext(addr);
                *(int *)GetNext(addr)=0;
                *(int *)(GetNext(addr)+sizeof(int))=0;
                *(int *)addr=NewSize-3*sizeof(int); ///Last edit
                void *nb=(addr+NewSize);//+3*sizeof(3));
                *(int *) nb = oldsizeNextBlock-(NewSize-oldSize)-3*sizeof(int);
                *(int *) (nb+sizeof(int))=NewSize;//+3*sizeof(int);
                *(int *)(nb+2*sizeof(int))=0;
                if(GetNext(nb)!=NULL)
                {
                    *(int *)(GetNext(nb)+sizeof(int))=(*(int *)nb+3*sizeof(int));
                }
                return addr;
            }
            else
            {
               int oldsizeNextBlock;
                oldsizeNextBlock=*(int *)GetNext(addr);
                *(int *)GetNext(addr)=0;
                *(int *)(GetNext(addr)+sizeof(int))=0;

                *(int *)addr=(*(int *)addr+oldsizeNextBlock+sizeof(int)*3);

                if((GetNext(addr))!=NULL)
                {
                    *(int *)(GetNext(addr)+sizeof(int))=(*(int *)addr+3*sizeof(int));
                }
                return addr;
            }
        }
        else
        {
            void* nb= CreateBlock(NewSize);
            if(nb) {
                for (int i = 0; i < NewSize; i++) {
                *(char *) (nb+sizeof(char))=*(char *)(addr+sizeof(char));
                }
                DeleteBlock(addr);
                return nb;
            }
            return NULL;
        }
    }
}
void* ListOfBlock::GetFirst()
{
    return mem;
}
void* ListOfBlock::GetLastAdress()
{
    return mem+sizeof(char)*len;
}
