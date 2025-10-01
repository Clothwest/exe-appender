#include "epd.h"
#include "cli.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE (1024 * 1024)

/*
	usage:
	epd -h
	epd -v
	epd <exe> -a <file> (-o <out>)
	epd <exe> -l
	epd <exe> -x <out_path>
*/

int main(int argc, char **argv) {
	option_t opt = { 0 };
	collectargs(argc, argv, &opt);
	set_cmd(&opt);
	run_cmd(&opt);
	return 0;
}
