#pragma once

#include "epd.h"

#include "utils.h"

#ifdef EPD_DEBUG

#define LOG(color, ...) \
set_console_color(color);\
printf(__VA_ARGS__);\
set_console_color(DEFAULT_COLOR)

#else

#define LOG(color, x)

#endif
