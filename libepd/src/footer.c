#include "footer.h"
#include "utils.h"

#include <stdio.h>
#include <string.h>

void set_footer(footer_t *footer, const char *exename, const char *appendfilename, uint64_t payload_len) {
	memcpy(footer->magic, MAGIC, MAGIC_SIZE);
	size_t exe_len = strlen(exename) < ENAME_LEN ? strlen(exename) : ENAME_LEN;
	memcpy(footer->exename, exename, exe_len);
	size_t append_len = strlen(appendfilename) < FNAME_LEN ? strlen(appendfilename) : FNAME_LEN;
	memcpy(footer->filename, appendfilename, append_len + 1);
	footer->payload_len = payload_len;
}

void fwrite_footer(footer_t *footer, FILE *fp) {
	fseek(fp, 0L, SEEK_END);
	fwrite(footer, sizeof(footer_t), 1, fp);
	printf("Written footer: magic = %s, exename = %s, filename = %s, payload_len = %llu\n", footer->magic, footer->exename, footer->filename, footer->payload_len);
}

void fread_footer(footer_t *footer, FILE *fp) {
	if (fseek(fp, -FTSIZE, SEEK_END) != 0) {
		errprintf("Failed to seek\n");
	}
	fread(footer, sizeof(footer_t), 1, fp);
}
