#pragma once

#define NULL ((void*)0)

void heap_init();

void* malloc();
void free(void* ptr);