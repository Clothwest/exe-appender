#pragma once

#include "epd.h"

#include <stdint.h>

typedef uint32_t opt_cmd;

typedef enum _cmd_id {
	CMD_NONE = 0,
	CMD_VERSION = 1 << 0,
	CMD_HELP = 1 << 1,
	CMD_LIST = 1 << 2,
	CMD_EXTRACT = 1 << 3,
	CMD_APPEND = 1 << 4
} cmd_id_t;

typedef enum _opt_id {
	OPT_UNKONWN = 0,
	OPT_VERSION,
	OPT_HELP,
	OPT_LIST ,
	OPT_EXTRACT,
	OPT_APPEND, 
	OPT_OUTPUT
} opt_id_t;

typedef struct _option {
	opt_cmd cmd;
	bool version;
	bool help;
	bool list;
	bool extract;
	const char *exe;
	const char *append;
	const char *output;
} option_t;

typedef int (*cmd_func_t)(option_t *opt);

typedef struct _cmd {
	cmd_id_t cmd_id;
	cmd_func_t cmd_func;
} cmd_t;

typedef struct _opt_entry {
	const char *name;
	int args;
	opt_id_t id;
} opt_entry_t;

EPD_API int collectargs(int argc, char **argv, option_t *opt);
EPD_API int set_cmd(option_t *opt);
EPD_API int run_cmd(option_t *opt);

// cmd function
EPD_API int cmd_version(option_t *opt);
EPD_API int cmd_help(option_t *opt);
EPD_API int cmd_list(option_t *opt);
EPD_API int cmd_extract(option_t *opt);
EPD_API int cmd_append(option_t *opt);
