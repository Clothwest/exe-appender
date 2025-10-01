#include "cmd_extract.h"
#include "footer.h"
#include "utils.h"

#include "cli.h"

#include <stdio.h>

#define BUF_SIZE (1024 * 1024)

static bool allocated = false;

int cmd_extract(option_t *opt) {
	if (!(opt->exe = extract(opt->exe))) {
		return 1;
	}
	return 0;
}

const char *extract(const char *exename) {
	FILE *fexe = epd_fopen(exename, "rb");
	fseek(fexe, 0L, SEEK_END);
	long size = ftell(fexe);
	footer_t footer = { 0 };
	char tail[TAIL_LEN + 1] = { 0 };
	fread_footer(&footer, fexe);
	fread(tail, 1, TAIL_LEN, fexe);
	if (memcmp(footer.magic, MAGIC, MAGIC_SIZE) != 0 || memcmp(tail, TAIL, TAIL_LEN) != 0) {
		printf("No appended file\n");
		return NULL;
	}
	long append_size = footer.payload_len;
	long exe_size = size - append_size - FTSIZE;
	if (fseek(fexe, -(FTSIZE + append_size), SEEK_END) != 0) {
		errprintf("Failed to seek\n");
	}
	rewind(fexe);
	char *buf = (char *)epd_malloc(BUF_SIZE);
	int n;
	long total = exe_size;
	FILE *foldexe = epd_fopen(footer.exename, "wb");
	FILE *ffile = epd_fopen(footer.filename, "wb");
	while ((n = fread(buf, 1, BUF_SIZE < total ? BUF_SIZE : total, fexe)) > 0) {
		fwrite(buf, 1, n, foldexe);
		total -= n;
	}
	total = append_size;
	while ((n = fread(buf, 1, BUF_SIZE < total ? BUF_SIZE : total, fexe)) > 0) {
		fwrite(buf, 1, n, ffile);
		total -= n;
	}
	free(buf);
	fclose(fexe);
	fclose(foldexe);
	fclose(ffile);
	printf("Extract:\n");
	printf("Source exe: %s\n", exename);
	printf("Output:\n");
	printf("Output exe: %s\n", footer.exename);
	printf("Output file: %s\n", footer.filename);
	char *exe = (char *)epd_malloc(sizeof(footer.exename));
	allocated = true;
	memcpy(exe, footer.exename, sizeof(footer.exename));
	return exe;
}

void xfree(void *ptr) {
	if (allocated) {
		free(ptr);
	}
}
