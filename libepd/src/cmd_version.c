#include "cmd_version.h"

#include "cli.h"

#include <stdio.h>

int cmd_version(option_t *opt)
{
	print_version();
	return 0;
}

void print_version(void)
{
	puts(VERSION_INFO);
}
