#include <iostream>
#include "Allocator.h"

using namespace std;

int main() {

    Allocator* allocator1=new Allocator(300);
    //allocator1->mem_dump();
    void* first= allocator1->mem_alloc(40);
    void* second= allocator1->mem_alloc(50);
    void* third= allocator1->mem_alloc(60);

    //allocator1->mem_dump();

    //cout<<"Break"<<endl;
    //allocator1->mem_free(third);
   // allocator1->mem_dump();

    //void* fourth=allocator1->mem_alloc(50);
    //fourth=allocator1->mem_realloc(fourth,30);
    TypeOfMemoryDump t=GlobalDumpInInt;

    allocator1->mem_dump(t);
    cout<<endl;
    allocator1->mem_realloc(first,44);
    allocator1->mem_free(second);
    allocator1->mem_dump(t);


    return 0;
}