#include "cmd_help.h"

#include "cli.h"

#include <stdio.h>

int cmd_help(option_t *opt)
{
	print_usage();
	return 0;
}

void print_usage(void)
{
	printf("Usage:\n");
	printf("epd -h | to get help\n");
	printf("epd -v | to get version\n");
	printf("epd <exe> -a <file> (-o <out>) | to append file\n");
	printf("epd <exe> -l | to list info of appended file\n");
	printf("epd <exe> -x | to unpack file\n");
}
