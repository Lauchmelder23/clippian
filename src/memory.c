#include "memory.h"

#include "io.h"
#include "convert.h"

struct FreeBlock
{
    size_t size;
    struct FreeBlock* next;
};

struct Block
{
    size_t size;
    void* data;
};

extern const void* __heap_base;
static struct FreeBlock* head = NULL;

void heap_init()
{
    head = (struct FreeBlock*)__heap_base;
    head->next = head + sizeof(struct FreeBlock);
    head->size = 0;

    head->next->next = NULL;
    head->next->size = -1;
}

struct FreeBlock* find_free_block(struct FreeBlock** previous, size_t min_size)
{
    struct FreeBlock* block = head;
    while(block && min_size < block->size)
    {
        *previous = block;
        block = block->next;
    }

    return block;
}

void* malloc(size_t size)
{
    size_t physicalSize = size + sizeof(size_t);
    struct Block* allocation = NULL;

    struct FreeBlock* previous = head;
    struct FreeBlock* block = find_free_block(&previous, physicalSize);

    allocation = (struct Block*)block;
    allocation->size = size;

    if(block->size == physicalSize)
    {
        previous->next = block->next;
    }
    else
    {
        struct FreeBlock* shrunkBlock = block + physicalSize;
        shrunkBlock->next = block->next;
        shrunkBlock->size = shrunkBlock->next - shrunkBlock;

        previous->next = shrunkBlock;
    }

    return &(allocation->data);
}

void free(void* ptr)
{
    struct FreeBlock* block = (struct FreeBlock*)((size_t*)ptr - 1);
    
    struct FreeBlock* previous = head;
    while(previous && (void*)previous->next < ptr)
        previous = previous->next; 

    previous->next = block;
    block->next = previous;
}