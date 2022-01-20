#include "io.h"
#include "convert.h"
#include "string.h"

void print_clippy();
char* get_user_input(char* buffer);

void main()
{
    const char* hex_chars = "0123456789ABCDEF";
    long int start = *(volatile long int*)0x50000;
    char buffer[1024];

    uart_init();
    print_clippy();
    uart_puts("Boot successful! \n");
    uart_puts("Started execution at 0x");
    uart_puts(ultoa(start, buffer, 16));

    for(;;)
    {
        uart_puts("\n\nPlease enter first operand\n");
        get_user_input(buffer);
        
        if(!strcmp(buffer, "clippy"))
        {
            print_clippy();
            continue;
        }

        int a = stoi(buffer);

        uart_puts("\nPlease enter second operand\n");
        int b = stoi(get_user_input(buffer));

        uart_puts("\n");
        uart_puts(itoa(a, buffer, 10));
        uart_puts(" * ");
        uart_puts(itoa(b, buffer, 10));
        uart_puts(" = ");
        uart_puts(itoa(a * b, buffer, 10));
    }
}

char* get_user_input(char* buffer)
{
    uart_puts("📎 "); 
    return uart_gets(buffer);
}

void print_clippy()
{
    uart_puts("    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   \n");
    uart_puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠠⡀⢄⢀⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ ⠀\n");
    uart_puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢐⠌⡢⢑⠌⠢⢑⢐⠅⡢⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    uart_puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⢤⣤⣴⢴⡦⣧⣌⠄⠀⠀⠀⠀⠀⠑⡰⠨⡊⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀  \n");
    uart_puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣟⣯⣷⣻⣽⣯⢷⣟⡆⠀⠀⠀⠀⠀⠀⠐⢅⢊⢌⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    uart_puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⢘⠨⡊⢔⠈⠉⠁⠀⠀⠀⠀⠀⠀⡤⡤⣅⣆⡢⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    uart_puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠊⠔⠌⠂⠀⠀⠀⠀⠀⠀⠀⠀⠘⢟⣿⢽⣷⣻⢷⢦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    uart_puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⢐⣨⡴⣤⣢⡈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠩⡊⡛⢟⣿⣻⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    uart_puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠈⣴⢿⡽⣯⢿⣞⡿⣎⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⠂⠑⠈⠄⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    uart_puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠄⠠⣻⣽⢿⡽⣯⢿⣽⣻⠀⡀⠀⠀⠀⠀⠠⣈⣤⢦⣦⣂⣁⠀⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    uart_puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠄⠀⠙⣾⣻⣽⣻⣽⢷⠋⠀⠀⠀⠀⠀⠈⣴⣟⣾⣻⣞⣿⣺⢧⠀⠈⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    uart_puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⡀⠁⠍⠑⠁⠁⠀⠀⠀⠀⠀⠀⡈⣾⣗⣯⣷⣻⣗⣿⣻⠀⠁⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    uart_puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠠⡠⢐⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠱⣯⡷⣟⣾⡽⣞⠏⡀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    uart_puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡑⢌⢂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠈⠙⠙⠓⢉⠈⢀⠀⠐⠀⠀⠠⠠⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    uart_puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡪⢐⠔⠀⠀⠀⠀⠠⡠⡀⠀⠀⠀⠀⠀⡅⠢⡁⠀⠀⠀⠀⠀⢀⢌⠪⠨⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    uart_puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡪⢐⠌⠀⠀⠀⠀⡑⡐⢌⠀⠀⠀⠀⠐⢌⠪⡀⠀⠀⠀⠀⠠⡑⢄⠕⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    uart_puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡪⢐⠡⠀⠀⠀⠀⠌⡌⠢⠀⠀⠀⠀⠈⡢⢑⠄⠀⠀⠀⠠⡑⢌⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    uart_puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢌⠢⡡⠀⠀⠀⠀⠡⡊⢌⠀⠀⠀⠀⠀⡪⢐⠌⠀⠀⠀⢌⢌⠢⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    uart_puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠢⡑⡐⡀⠀⠀⠀⠡⢊⠔⡀⠀⠀⠀⠀⢌⠢⡑⠀⠀⠀⡢⠢⠡⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    uart_puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢈⠢⡑⡀⠀⠀⠀⠈⡢⢑⠄⠀⠀⠀⠀⢐⠅⡊⠄⠀⠀⡊⢌⢊⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    uart_puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⢑⠔⡐⡀⠀⠀⠀⢌⢂⠪⠀⠀⠀⠀⢐⠅⡪⠀⠀⠀⢌⠢⠡⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    uart_puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ ⠀⠀⠡⡊⠔⢄⠀⠀⠀⠀⠪⠨⡊⢄⢀⢀⠢⡑⡐⠁⠀⠀⠠⡑⠅⠅⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    uart_puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⠌⡪⢐⠄⠀⠀⠀⠈⠈⠢⠡⠢⡡⢑⠐⠁⠀⠀⠀⠀⡪⠨⡂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    uart_puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ ⠀⠀⠀⠀⠨⢂⢅⠢⠀⠀⠀⠀⠀⠀⠁⠁⠀⠀⠀⠀⠀⠀⠀⠀⢌⢌⠢⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    uart_puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠡⢂⠕⡡⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢅⠢⡡⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    uart_puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⠡⠢⡡⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠨⡂⢕⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    uart_puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ ⠀⠀⠀⠀⠀⠀⠀⠈⢊⠔⡑⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢄⠣⠨⡂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    uart_puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ ⠀⠀⠀⠀⠀⠊⢔⠡⡡⡁⡀⢀⠀⠀⡀⢀⠌⢌⠢⠡⡃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    uart_puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠑⡐⠌⡌⡂⡊⡢⢊⠔⢌⠢⠑⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    uart_puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠈⠂⠈⠂⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ \n");
    uart_puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ ⠀⠀ ⠀⠀⠀⠀⠀ ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");

}