#include "memory.h"

#include "stdint.h"
#include "io.h"
#include "convert.h"

struct FreeBlock
{
    struct FreeBlock* next;
};

#define HEAP_BASE ((void*)0x40000000)
#define BLOCK_SIZE 4096
#define MAGIC_NUMBER 0xDEADBEEF

static struct FreeBlock* head = (struct FreeBlock*)HEAP_BASE;

void heap_init()
{
    head->next = NULL;
}

void* malloc()
{
    void* block = (void*)head;

    if(head->next == NULL)
    {
        head += BLOCK_SIZE;
        head->next = NULL;
    }
    else
    {
        head = head->next;
    }

    *(uint32_t*)block = MAGIC_NUMBER;
    return block + sizeof(uint32_t);
}

void free(void* ptr)
{
    void* blockStart = ptr - sizeof(uint32_t);
    if(*(uint32_t*)blockStart != MAGIC_NUMBER)
        return;

    if((struct FreeBlock*)blockStart < head)
    {
        struct FreeBlock* nextBlock = head->next;
        head = blockStart;
        head->next = nextBlock;
        return;
    }

    struct FreeBlock* block = head;

    while(block)
    {
        if(block < (struct FreeBlock*)blockStart && (struct FreeBlock*)blockStart < block->next)
        {
            struct FreeBlock* newBlock = (struct FreeBlock*)blockStart;
            newBlock->next = block->next;
            block->next = newBlock;

            return;
        }

        block = block->next;
    }
}