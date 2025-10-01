#include "cmd_append.h"
#include "footer.h"
#include "utils.h"
#include "cmd_extract.h"

#include "cli.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUF_SIZE (1024 * 1024)

int cmd_append(option_t *opt) {
	char buf[MAX_PATH] = { 0 };
	opt->output = set_output_filename(opt->output, opt->exe, opt->append, buf, MAX_PATH);
	return append_file_with_footer(opt->exe, opt->append, opt->output);
}

const char *set_output_filename(const char *output, const char *exe, const char *append, char *buf, size_t buf_size) {
	if (output) {
		return output;
	}
	time_t now = time(NULL);
	struct tm *tm_now = localtime(&now);
	char timestr[16];
	strftime(timestr, sizeof(timestr), "%Y%m%d_%H%M%S", tm_now);
	snprintf(buf, buf_size, "%s-%s-%s.exe", exe, append, timestr);
	return (output = buf);
}

int append_file_with_footer(const char *exename, const char *appendfilename, const char *output) {
	FILE *fexe = epd_fopen(exename, "rb");
	FILE *fappend = epd_fopen(appendfilename, "rb");
	FILE *fout = epd_fopen(output, "wb");
	char *buf = (char *)epd_malloc(BUF_SIZE);

	// exe
	size_t total = epd_fcpy(fout, fexe, buf, BUF_SIZE);
	printf("Copied %s: %zu bytes\n",exename , total);

	// appendfile
	size_t append_len = epd_fcpy(fout, fappend, buf, BUF_SIZE);
	printf("Copied %s: %zu bytes\n", appendfilename, append_len);

	// footer
	footer_t footer = { 0 };
	set_footer(&footer, exename, appendfilename, append_len);
	fwrite_footer(&footer, fout);

	// magic tail
	fwrite(TAIL, TAIL_LEN, 1, fout);
	printf("Written magic tail: %s\n", TAIL);

	free(buf);
	fclose(fexe);
	fclose(fappend);
	fclose(fout);
	xfree(exename);
	printf("Created output file: %s\n", output);
	return 0;
}
