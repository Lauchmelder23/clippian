#include "mb.h"
#include "gpio.h"
#include "memory.h"
#include "io.h"
#include "convert.h"

volatile uint32_t __attribute__((aligned(16))) mailbox[36];

enum
{
    VIDEOCORE_MAILBOX   = (PERIPHERAL_BASE + 0x0000B880),
    MAILBOX_READ        = (VIDEOCORE_MAILBOX + 0x0),
    MAILBOX_POLL        = (VIDEOCORE_MAILBOX + 0x10),
    MAILBOX_SENDER      = (VIDEOCORE_MAILBOX + 0x14),
    MAILBOX_STATUS      = (VIDEOCORE_MAILBOX + 0x18),
    MAILBOX_CONFIG      = (VIDEOCORE_MAILBOX + 0x1C),
    MAILBOX_WRITE       = (VIDEOCORE_MAILBOX + 0x20),

    MAILBOX_RESPONSE    = 0x80000000,
    MAILBOX_FULL        = 0x80000000,
    MAILBOX_EMPTY       = 0x40000000
};

struct BufferHeader
{
    uint32_t size;
    uint32_t status_code;
};

struct TagHeader
{
    uint32_t identifier;
    uint32_t buf_size;
    uint32_t status_code;
};

uint32_t mailbox_call(uint8_t ch)
{
    uint32_t r = ((uint32_t)((int64_t)&mailbox) & ~0xF) | (ch & 0xF);

    while(peek(MAILBOX_STATUS) & MAILBOX_FULL);

    poke(MAILBOX_WRITE, r);

    for(;;)
    {
        while(peek(MAILBOX_STATUS) & MAILBOX_EMPTY);

        if(r == peek(MAILBOX_READ))
            return mailbox[1] == MAILBOX_RESPONSE;
    }

    return 0;
}

struct BufferHeader* alloc_buffer()
{
    return (struct BufferHeader*)malloc();
}

void free_buffer(struct BufferHeader* ptr)
{
    free((void*)ptr);
}

uint8_t* create_tag(uint8_t* ptr, uint32_t identifier, uint8_t* buffer, uint32_t size)
{
    struct TagHeader* header = (struct TagHeader*)ptr;
    header->identifier = identifier;
    header->buf_size = size;
    header->status_code = 0;

    ptr = (uint8_t*)(header + 1);
    for(uint32_t i = 0; i < size; i++)
    {
        *ptr++ = *buffer++;
    }

    uint8_t padding = size % 4;
    if(padding)
        ptr += 4 - padding;

    return ptr;
}

uint32_t get_vc_firmware_rev(void)
{
    mailbox[0] = 7 * sizeof(uint32_t);  // buffer size
    mailbox[1] = 0;     // request code
    mailbox[2] = 1;     // tag identifier
    mailbox[3] = sizeof(uint32_t);     // tag buffer size
    mailbox[4] = 0;     // tag request code
    mailbox[5] = 0;     // tag content
    mailbox[6] = 0;     // end tag

    mailbox_call(8);

    return mailbox[5];
}

uint8_t* get_board_mac_address(uint8_t* buffer)
{
    mailbox[0] = 8 * sizeof(uint32_t);  // buffer size
    mailbox[1] = 0;     // request code
    mailbox[2] = 0x00010003;     // tag identifier
    mailbox[3] = 6 * sizeof(uint8_t);     // tag buffer size
    mailbox[4] = 0;     // tag request code

    mailbox[5] = 0;     // tag content
    mailbox[6] = 0;

    mailbox[7] = 0;     // end tag

    mailbox_call(8);

    uint8_t* mac_address = (uint8_t*)(mailbox + 5);
    for(uint8_t i = 0; i < 6; i++)
        buffer[i] = mac_address[i];

    return buffer;
}