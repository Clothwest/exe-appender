#pragma once

#include "epd.h"

#include <stdio.h>

#define DEFAULT_COLOR (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
#define RED (FOREGROUND_RED | FOREGROUND_INTENSITY)
#define GREEN (FOREGROUND_GREEN | FOREGROUND_INTENSITY)

#define errprintf(...) \
fprintf(stderr, __VA_ARGS__);\
exit(EXIT_FAILURE)

EPD_API FILE *epd_fopen(const char *filename, const char *mode);
EPD_API size_t epd_fcpy(FILE *dst, FILE *src, char *buf, size_t buf_size);
EPD_API void *epd_malloc(size_t size);

EPD_API bool set_console_color(WORD color);
