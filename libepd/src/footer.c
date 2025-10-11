#include "footer.h"
#include "utils.h"

#include <stdio.h>
#include <string.h>

char footer_exename[ENAME_SIZE];

void set_footer(footer_t *footer, const char *exepath, const char *appendfilepath, fsize_t payload_len)
{
	const char *exename = get_fname(exepath);
	const char *appendfilename = get_fname(appendfilepath);
	memcpy(footer->magic, MAGIC, MAGIC_SIZE);
	size_t exe_len = strlen(exename) < ENAME_LEN ? strlen(exename) : ENAME_LEN;
	memcpy(footer->exename, exename, exe_len);
	size_t append_len = strlen(appendfilename) < FNAME_LEN ? strlen(appendfilename) : FNAME_LEN;
	memcpy(footer->filename, appendfilename, append_len + 1);
	footer->payload_len = payload_len;
	memcpy(footer->tail, TAIL, TAIL_SIZE);
}

void fread_footer(footer_t *footer, FILE *stream)
{
	epd_fseek(stream, -FT_FSIZE, SEEK_END);
	epd_fread(footer, FT_FSIZE, 1, stream);
}

void fwrite_footer(footer_t *footer, FILE *stream)
{
	epd_fseek(stream, 0, SEEK_END);
	epd_fwrite(footer, FT_FSIZE, 1, stream);
	printf("Written footer: magic = %s, exename = %s, filename = %s, payload_len = %llu, tail = %s\n", footer->magic, footer->exename, footer->filename, footer->payload_len, footer->tail);
}
