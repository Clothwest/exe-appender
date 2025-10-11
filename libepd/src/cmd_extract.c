#include "cmd_extract.h"
#include "footer.h"
#include "utils.h"

#include "cli.h"

#include <stdio.h>

#define BUF_SIZE (1024 * 1024)

int cmd_extract(option_t *opt)
{
	if (!(opt->exe = extract(opt->exe)))
	{
		return 1;
	}
	return 0;
}

const char *extract(const char *exepath)
{
	FILE *fexe = epd_fopen(exepath, "rb");

	footer_t footer = { 0 };
	fread_footer(&footer, fexe);
	if (memcmp(footer.magic, MAGIC, MAGIC_SIZE) != 0 || memcmp(footer.tail, TAIL, TAIL_LEN) != 0)
	{
		printf("No appended file\n");
		epd_fclose(fexe);
		return NULL;
	}

	fsize_t size = epd_fsize(fexe);
	fsize_t append_size = footer.payload_len;
	fsize_t exe_size = size - append_size - FT_FSIZE;
	char *buf = (char *)epd_malloc(BUF_SIZE);
	FILE *foldexe = epd_fopen(footer.exename, "wb");
	FILE *ffile = epd_fopen(footer.filename, "wb");
	size_t n;
	fsize_t total;
	rewind(fexe);

	total = exe_size;
	while ((n = epd_fread(buf, 1, BUF_SIZE < total ? BUF_SIZE : total, fexe)) > 0)
	{
		epd_fwrite(buf, 1, n, foldexe);
		total -= n;
	}

	total = append_size;
	while ((n = epd_fread(buf, 1, BUF_SIZE < total ? BUF_SIZE : total, fexe)) > 0)
	{
		epd_fwrite(buf, 1, n, ffile);
		total -= n;
	}

	epd_free(buf);
	epd_fclose(fexe);
	epd_fclose(foldexe);
	epd_fclose(ffile);
	printf("Extract:\n");
	printf("Source exe: %s\n", exepath);
	printf("Output:\n");
	printf("Output exe: %s\n", footer.exename);
	printf("Output file: %s\n", footer.filename);
	memcpy(footer_exename, footer.exename, sizeof(footer.exename));
	return footer_exename;
}
