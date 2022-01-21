#pragma once

#include "stdint.h"

#define NULL ((void*)0)

void heap_init();

void* malloc(size_t size);
void free(void* ptr);