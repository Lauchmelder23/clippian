#include "mb.h"
#include "gpio.h"
#include "memory.h"
#include "io.h"
#include "convert.h"
#include "framebuffer.h"

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

void create_framebuffer(struct FrameBuffer* buffer, unsigned int width, unsigned int height)
{
    mailbox[0] = 35 * sizeof(uint32_t);  // buffer size
    mailbox[1] = 0;

    // Set physical display dimensions
    mailbox[2] = 0x00048003;
    mailbox[3] = 2 * sizeof(uint32_t);
    mailbox[4] = 0;
    mailbox[5] = width;
    mailbox[6] = height;

    // Set virtual display dimensions
    mailbox[7] = 0x00048004;
    mailbox[8] = 2 * sizeof(uint32_t);
    mailbox[9] = 0;
    mailbox[10] = width;
    mailbox[11] = height;

    // Set bit depth
    mailbox[12] = 0x00048005;
    mailbox[13] = 1 * sizeof(uint32_t);
    mailbox[14] = 0;
    mailbox[15] = 32;

    // Set pixel order
    mailbox[16] = 0x00048006;
    mailbox[17] = 1 * sizeof(uint32_t);
    mailbox[18] = 0;
    mailbox[19] = 1;

    // Set virtual offset
    mailbox[20] = 0x00048009;
    mailbox[21] = 2 * sizeof(uint32_t);
    mailbox[22] = 0;
    mailbox[23] = 0;
    mailbox[24] = 0;

    // Allocate buffer
    mailbox[25] = 0x00040001;
    mailbox[26] = 8;
    mailbox[27] = 0;
    mailbox[28] = 4096; 
    mailbox[29] = 0;

    // Get pitch
    mailbox[30] = 0x00040008;
    mailbox[31] = 1 * sizeof(uint32_t);
    mailbox[32] = 0;
    mailbox[33] = 0;

    mailbox[34] = 0;

    mailbox_call(8);

    mailbox[28] &= 0x3FFFFFFF;

    buffer->physicalDisplay.width = mailbox[5];
    buffer->physicalDisplay.height = mailbox[6];

    buffer->virtualDisplay.width = mailbox[10];
    buffer->virtualDisplay.height = mailbox[11];
    buffer->virtualDisplay.xOffset = mailbox[23];
    buffer->virtualDisplay.yOffset = mailbox[24];

    buffer->bitsPerPixel = mailbox[15];
    buffer->pitch = mailbox[33];
    buffer->pixels = (uint8_t*)((uint64_t)mailbox[28]);
    buffer->size = mailbox[29];
}