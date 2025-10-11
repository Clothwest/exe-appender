#include "utils.h"
#include "debug.h"

#include <stdlib.h>

void *epd_malloc(size_t size)
{
	void *p = malloc(size);
	if (!p)
	{
		errprintf("Failed to allocate memory\n");
	}
	return p;
}

void epd_free(void *block)
{
	free(block);
}

FILE *epd_fopen(const char *filename, const char *mode)
{
	FILE *fp = fopen(filename, mode);
	if (!fp)
	{
		errprintf("Failed to open %s\n", filename);
	}
	return fp;
}

int epd_fclose(FILE *stream)
{
	if (fclose(stream) != 0)
	{
		errprintf("Failed to close file\n");
	}
	return 0;
}

fsize_t epd_fread(void *buffer, fsize_t elementsize, fsize_t elementcount, FILE *stream)
{
	return fread(buffer, elementsize, elementcount, stream);
}

fsize_t epd_fwrite(void *buffer, fsize_t elementsize, fsize_t elementcount, FILE *stream)
{
	return fwrite(buffer, elementsize, elementcount, stream);
}

fsize_t epd_fcpy(FILE *dst, FILE *src, void *buf, fsize_t buf_size)
{
	fsize_t n = 0, size = 0;
	while ((n = epd_fread(buf, 1, buf_size, src)) > 0)
	{
		epd_fwrite(buf, 1, n, dst);
		LOG(GREEN, "Copied: %llu\n", n);
		size += n;
	}
	return size;
}

fsize_t epd_fsize(FILE *stream)
{
	foffset_t cur_pos = epd_ftell(stream);
	epd_fseek(stream, 0, SEEK_END);
	fsize_t size = epd_ftell(stream);
	epd_fseek(stream, cur_pos, SEEK_SET);
	return size;
}

int epd_fseek(FILE *stream, foffset_t offset, int origin)
{
	if (fseek64(stream, offset, origin) != 0)
	{
		errprintf("Failed to seek\n");
	}
	return 0;
}

foffset_t epd_ftell(FILE *stream)
{
	foffset_t pos = ftell64(stream);
	if (pos == -1L)
	{
		errprintf("Failed to tell\n");
	}
	return pos;
}

const char *get_fname(const char *fpath)
{
	size_t len = strlen(fpath);
	const char *fname = fpath + len;
	while (fname != fpath && !is_path_separator(*(fname - 1)))
	{
		fname--;
	}
	return fname;
}

bool is_path_separator(const char ch)
{
	return ch == '\\' || ch == '/';
}

bool set_console_color(WORD color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	return SetConsoleTextAttribute(hConsole, color);
}
