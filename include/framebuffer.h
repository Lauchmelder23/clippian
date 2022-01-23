#pragma once

#include "stdint.h"

struct FrameBuffer
{
    struct 
    {
        uint32_t width;
        uint32_t height;
    } physicalDisplay;

    struct 
    {
        uint32_t width;
        uint32_t height;
        uint32_t xOffset;
        uint32_t yOffset;
    } virtualDisplay;

    uint32_t pitch;
    uint32_t bitsPerPixel;
    uint8_t* pixels;
    uint32_t size;
};

struct FrameBuffer* framebuffer_init(unsigned int width, unsigned int height);
void framebuffer_release(void);

void draw_test_image(void);
void draw_clippy(unsigned int x, unsigned int y);