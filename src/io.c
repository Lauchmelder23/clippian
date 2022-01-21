#include "io.h"
#include "gpio.h"

// Mini UART registers
enum
{
    AUX_BASE    =   0xFE000000 + 0x215000,

    AUX_ENABLES     = AUX_BASE + 0x04,
    AUX_MU_IO_REG   = AUX_BASE + 0x40,
    AUX_MU_IER_REG  = AUX_BASE + 0x44,
    AUX_MU_IIR_REG  = AUX_BASE + 0x48,
    AUX_MU_LCR_REG  = AUX_BASE + 0x4C,
    AUX_MU_MCR_REG  = AUX_BASE + 0x50,
    AUX_MU_LSR_REG  = AUX_BASE + 0x54,
    AUX_MU_CNTL_REG = AUX_BASE + 0x60,
    AUX_MU_STAT_REG = AUX_BASE + 0x64,
    AUX_MU_BAUD_REG = AUX_BASE + 0x68,

    AUX_UART_CLOCK  = 500000000,
    UART_MAX_QUEUE  = 16 * 1024
};

void uart_init()
{
    poke(AUX_ENABLES, 1);       // Enable UART1
    poke(AUX_MU_LCR_REG, 3);    // 8 bit communication
    poke(AUX_MU_MCR_REG, 0);    // Pull RTS high
    poke(AUX_MU_IER_REG, 0);
    poke(AUX_MU_IIR_REG, 0xC6); // Disable interrupts
    poke(AUX_MU_BAUD_REG, AUX_UART_CLOCK / (115200 * 8) - 1);
    gpio_setAltMode5(14);
    gpio_setAltMode5(15);
    poke(AUX_MU_CNTL_REG, 3);
}

uint32_t uart_isReceiveFIFOReady()  { return peek(AUX_MU_LSR_REG) & 1; }
uint32_t uart_isTransmitFIFOReady() { return peek(AUX_MU_LSR_REG) & (1 << 5); }

void uart_writeBlocking(uint8_t ch)
{
    while(!uart_isTransmitFIFOReady());
    poke(AUX_MU_IO_REG, (uint32_t)ch);
}

char uart_getchar()
{
    while(!uart_isReceiveFIFOReady());
    char in = (char)peek(AUX_MU_IO_REG);
    uart_putchar(in);
    if(in == '\r')
        uart_writeBlocking('\n');
    return in;
}

char* uart_gets(char* string)
{
    char* start = string;
    do
    {
        *string = uart_getchar();
    } while(*string++ != '\r');

    *(string - 1) = '\0';
    return start;
}

void uart_putchar(char ch)
{
    if(ch == '\n')
        uart_writeBlocking('\r');
    uart_writeBlocking(ch);
}

void uart_puts(const char* string)
{
    while(*string) 
        uart_putchar(*string++);
}