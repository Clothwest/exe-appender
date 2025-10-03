#pragma once

#include "epd.h"

#include <stdio.h>
#include <stdint.h>

#define DEFAULT_COLOR (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
#define RED (FOREGROUND_RED | FOREGROUND_INTENSITY)
#define GREEN (FOREGROUND_GREEN | FOREGROUND_INTENSITY)

#define errprintf(...) \
fprintf(stderr, __VA_ARGS__);\
exit(EXIT_FAILURE)

#define fseek64 _fseeki64
#define ftell64 _ftelli64

typedef uint64_t fsize_t;
typedef int64_t foffset_t;

EPD_API void *epd_malloc(size_t size);
EPD_API void epd_free(void *block);
EPD_API FILE *epd_fopen(const char *filename, const char *mode);
EPD_API int epd_fclose(FILE *stream);
EPD_API fsize_t epd_fread(void *buffer, fsize_t elementsize, fsize_t elementcount, FILE *stream);
EPD_API fsize_t epd_fwrite(void *buffer, fsize_t elementsize, fsize_t elementcount, FILE *stream);
EPD_API fsize_t epd_fcpy(FILE *dst, FILE *src, void *buf, fsize_t buf_size);
EPD_API fsize_t epd_fsize(FILE *stream);
EPD_API int epd_fseek(FILE *stream, foffset_t offset, int origin);
EPD_API foffset_t epd_ftell(FILE *stream);

EPD_API const char *get_fname(const char *fpath);
EPD_API bool is_path_separator(const char ch);

EPD_API bool set_console_color(WORD color);
