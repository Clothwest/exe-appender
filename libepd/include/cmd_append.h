#pragma once

#include "epd.h"
#include "footer.h"

EPD_API const char *set_output_filename(const char *output, const char *exe, const char *append, char *buf, size_t buf_size);
EPD_API int append_file_with_footer(const char *exepath, const char *appendfilepath, const char *output);
