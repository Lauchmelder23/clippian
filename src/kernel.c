#include "io.h"
#include "convert.h"
#include "string.h"
#include "memory.h"
#include "mb.h"
#include "framebuffer.h"

void print_clippy();
char* get_user_input(char* buffer);

void main()
{
    extern long _start;
    char buffer[1024];
    uint8_t mac_address[6];

    uart_init();
    heap_init();

    print_clippy();
    uart_puts("Boot successful! \n");

    uart_puts("Firmware revision: ");
    uart_puts(utoa(get_vc_firmware_rev(), buffer, 10));

    get_board_mac_address(mac_address);
    uart_puts("\nMAC Address: ");
    for(uint8_t i = 0; i < 6; i++)
    {
        uart_puts(utoa(mac_address[i], buffer, 16));
        if(i != 5)
            uart_puts(":");
    }
    uart_puts("\n");
    
    uart_puts("\n");
    uart_puts("Started execution at 0x");
    uart_puts(ultoa((long)&_start, buffer, 16));

    struct FrameBuffer* framebuffer = framebuffer_init(1920, 1080);
    uart_puts("\n\nFramebuffer info\n---------------\n");
    uart_puts("Physical display  : ");  uart_puts(utoa(framebuffer->physicalDisplay.width, buffer, 10));    uart_puts("x"); uart_puts(utoa(framebuffer->physicalDisplay.height, buffer, 10));  uart_puts(" pixels\n");
    uart_puts("Virtual display   : ");  uart_puts(utoa(framebuffer->virtualDisplay.width, buffer, 10));    uart_puts("x"); uart_puts(utoa(framebuffer->virtualDisplay.height, buffer, 10));  uart_puts(" pixels\n");
    uart_puts("Virt. disp. offset: ("); uart_puts(utoa(framebuffer->virtualDisplay.xOffset, buffer, 10));    uart_puts(","); uart_puts(utoa(framebuffer->virtualDisplay.yOffset, buffer, 10));  uart_puts(")\n");
    uart_puts("Pitch:            : ");  uart_puts(utoa(framebuffer->pitch, buffer, 10));    uart_puts(" bytes\n");
    uart_puts("Bit depth         : ");  uart_puts(utoa(framebuffer->bitsPerPixel, buffer, 10)); uart_puts(" bits per pixel\n");
    uart_puts("Memory location   : 0x");  uart_puts(ultoa((unsigned long)framebuffer->pixels, buffer, 16));   uart_puts("\n");
    uart_puts("Size              : ");  uart_puts(utoa(framebuffer->size, buffer, 10)); uart_puts(" bytes\n\n");

    draw_test_image();
    draw_clippy(100, 100);

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