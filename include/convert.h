#pragma once

#include "stdint.h"

int stoi(const char* string);

char* ultoa(unsigned long number, char* string, int base);
char* ltoa(long number, char* string, int base);
char* utoa(unsigned int number, char* string, int base);
char* itoa(int number, char* string, int base);