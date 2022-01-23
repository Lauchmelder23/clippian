#include "framebuffer.h"

#include "mb.h"
#include "memory.h"
#include "io.h"
#include "clippy.h"

static struct FrameBuffer framebuffer;

struct FrameBuffer* framebuffer_init(unsigned int width, unsigned int height)
{
    create_framebuffer(&framebuffer, width, height);

    return &framebuffer;
}

void framebuffer_release(void)
{
    
}

void draw_test_image(void)
{
    for(uint32_t y = 0; y < framebuffer.virtualDisplay.height; y++)
    {
        for(uint32_t x = 0; x < framebuffer.virtualDisplay.width; x++)
        {
            size_t offset = y * framebuffer.pitch + (x * (framebuffer.bitsPerPixel / 8));

            framebuffer.pixels[offset + 3] = 255;
            framebuffer.pixels[offset + 2] = y * 255 / framebuffer.virtualDisplay.height;
            framebuffer.pixels[offset + 1] = x * 255 / framebuffer.virtualDisplay.width;
            framebuffer.pixels[offset + 0] = 255;
        }
    }
}

void draw_clippy(unsigned int xoff, unsigned int yoff)
{
    for(uint32_t y = 0; y < clippy_width; y++)
    {
        for(uint32_t x = 0; x < clippy_width; x++)
        {
            size_t offset = (yoff + y) * framebuffer.pitch + ((xoff + x) * (framebuffer.bitsPerPixel / 8));

            framebuffer.pixels[offset + 3] = 255;
            framebuffer.pixels[offset + 2] = clippy_pixels[y * (clippy_width * 3) + (x * 3) + 0];
            framebuffer.pixels[offset + 1] = clippy_pixels[y * (clippy_width * 3) + (x * 3) + 1];
            framebuffer.pixels[offset + 0] = clippy_pixels[y * (clippy_width * 3) + (x * 3) + 2];
        }
    }
}