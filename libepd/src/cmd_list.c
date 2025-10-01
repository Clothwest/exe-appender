#include "cmd_list.h"
#include "utils.h"
#include "footer.h"

#include "cli.h"

#include <stdio.h>

int cmd_list(option_t *opt) {
	return print_list(opt);
	//return 0;
}

int print_list(option_t *opt) {
	FILE *fexe = epd_fopen(opt->exe, "rb");
	footer_t footer = { 0 };
	char tail[TAIL_LEN + 1] = { 0 };
	fread_footer(&footer, fexe);
	fread(tail, 1, TAIL_LEN, fexe);
	if (memcmp(footer.magic, MAGIC, MAGIC_SIZE) != 0 || memcmp(tail, TAIL, TAIL_LEN != 0)) {
		printf("No appended file\n");
		fclose(fexe);
		return 1;
	}
	printf("Exe file: \t%s\n", footer.exename);
	printf("Appended file: \t%s\n", footer.filename);
	printf("Size: \t\t%llu bytes\n", footer.payload_len);
	fclose(fexe);
	return 0;
}
