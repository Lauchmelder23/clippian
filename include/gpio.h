#include "stdint.h"

// Functions for peeking/poking into memory
void     poke(int64_t addr, uint32_t val);
uint32_t peek(int64_t addr);


int32_t gpio_call(uint32_t pin, uint32_t reg, uint32_t value, uint32_t field_size);

uint32_t gpio_set    (uint32_t pin, uint32_t value);
uint32_t gpio_clear  (uint32_t pin, uint32_t value);
uint32_t gpio_fselect(uint32_t pin, uint32_t value);
uint32_t gpio_pull   (uint32_t pin, uint32_t value);

void gpio_setAltMode5(uint32_t pin);