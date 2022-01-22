#include "gpio.h"

void poke(int64_t addr, uint32_t val)
{
    *(volatile uint32_t*)addr = val;
}

uint32_t peek(int64_t addr)
{
    return *(volatile uint32_t*)addr;
}

enum
{
    GPFSEL0         = PERIPHERAL_BASE + 0x200000,
    GPSET0          = PERIPHERAL_BASE + 0x20001C,
    GPCLR0          = PERIPHERAL_BASE + 0x200028,
    GPPUPPDN0       = PERIPHERAL_BASE + 0x2000E4
};

enum
{
    MAX_PINS = 57
};

int32_t gpio_call(uint32_t pin, uint32_t reg, uint32_t value, uint32_t field_size)
{
    // Calculate a mask for the field. The mask is a string of 1's that is field_size long
    uint32_t field_mask = (1 << field_size) - 1;

    // Can't access pins that don't exist
    if(pin > MAX_PINS) return 0;
    
    // Can't write values that exceed the width of the field
    if(value > field_mask) return 0;

    uint32_t fields_per_register = 32 / field_size;                     // Number of fields per register
    uint32_t register_addr = reg + (pin / fields_per_register) * 4;     // Offset of register to base register. E.g. GPSET1 = GPSET0 + 4 bytes
    uint32_t field_offset = (pin % fields_per_register) * field_size;   // Number of bits the field is offset into the register

    uint32_t current_value = peek(register_addr);                       
    current_value &= ~(field_mask << field_offset);     // zero the field
    current_value |= value << field_offset;             // set the field
    poke(register_addr, current_value);                 // poke back into memory

    return 1;
}

uint32_t gpio_set(uint32_t pin, uint32_t value) 
{ 
    return gpio_call(pin, GPSET0, value, 1); 
}

uint32_t gpio_clear(uint32_t pin, uint32_t value) 
{ 
    return gpio_call(pin, GPCLR0, value, 1); 
}

uint32_t gpio_fselect(uint32_t pin, uint32_t value) 
{ 
    return gpio_call(pin, GPFSEL0, value, 3); 
}

uint32_t gpio_pull(uint32_t pin, uint32_t value) 
{ 
    return gpio_call(pin, GPPUPPDN0, value, 2); 
}

void gpio_setAltMode5(uint32_t pin)
{
    // UART1 requires the pins to float
    gpio_pull(pin, 0);
    gpio_fselect(pin, 2);
}