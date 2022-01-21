#include "convert.h"
#include "io.h"
#include "memory.h"

int stoi(const char* string)
{
    int output = 0;
    int32_t sign = 1;
    if(*string == '-')
    {
        string++;
        sign = -1;
    }


    while(*string >= '0' && *string <= '9')
    {
        output *= 10;
        output += sign * (*string++ - '0');
    }

    return output;
}

char* ultoa(unsigned long number, char* string, int base)
{
    if(base < 2 || base > 16)
    {
        string[0] = '\0';
        return string;
    }

    char* buffer = (char*)malloc(1024);
    char* temp = buffer;

    int i = 0;
    if(number == 0)
    {
        temp[i++] = '0';
    }
    else
    {
        for(; number > 0; number /= base)
        {
            uint8_t digit = number % base;

            if(digit < 10)
                temp[i++] = '0' + digit;
            else
                temp[i++] = 'A' + digit;
        }
    }

    temp[i] = '\0';
    string[i] = '\0';

    while(*temp)
    {
        string[--i] = *temp++;
    }

    free(buffer);
    return string;
}

char* ltoa(long number, char* string, int base)
{
    char* old_string = string;
    if(number < 0)
    {
        number *= -1;
        *string++ = '-';
    }
    
    ultoa(number, string, base);
    return old_string;
}

char* utoa(unsigned int number, char* string, int base)
{
    return ultoa(number, string, base);
}

char* itoa(int number, char* string, int base)
{
     return ltoa(number, string, base);
}