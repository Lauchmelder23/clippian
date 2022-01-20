#pragma once

#include "stdint.h"

void uart_init();

void uart_putchar(char c);
void uart_puts(const char* string);

char uart_getchar();
char* uart_gets(char* string);