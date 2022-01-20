#include "string.h"

int strcmp(const char* str1, const char* str2)
{
    while(*str1)
    {
        int diff = *str1++ - *str2++;
        if(diff) return diff;
    }

    return 0;
}