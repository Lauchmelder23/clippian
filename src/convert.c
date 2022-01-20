#include "convert.h"
#include "io.h"

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

char* itoa(int number, char* string)
{
    volatile char* temp = (volatile char*)0x40000000;
    int i = 0;
    if(number == 0)
    {
        temp[i++] = '0';
    }
    else
    {
        for(int n = (number < 0 ? -number : number); n > 0; n /= 10)
        {
            temp[i++] = '0' + (n % 10);
        }
    }

    if(number < 0)
    {
        temp[i++] = '-';
    }

    temp[i] = '\0';
    string[i] = '\0';

    while(*temp)
    {
        string[--i] = *temp++;
    }

    return string;
}