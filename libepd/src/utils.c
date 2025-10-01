#include "utils.h"
#include "debug.h"

#include <stdlib.h>

FILE *epd_fopen(const char *filename, const char *mode) {
	FILE *fp = fopen(filename, mode);
	if (!fp) {
		errprintf("Failed to open %s\n", filename);
	}
	return fp;
}

size_t epd_fcpy(FILE *dst, FILE *src, char *buf, size_t buf_size) {
	size_t n = 0, size = 0;
	while ((n = fread(buf, 1, buf_size, src)) > 0) {
		fwrite(buf, 1, n, dst);
		LOG(GREEN, "Copied: %zu\n", n);
		size += n;
	}
	return size;
}

void *epd_malloc(size_t size) {
	void *p = malloc(size);
	if (!p) {
		errprintf("Failed to allocate memory\n");
	}
	return p;
}

bool set_console_color(WORD color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	return SetConsoleTextAttribute(hConsole, color);
}
