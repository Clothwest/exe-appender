#include "cli.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static opt_entry_t options[] = {
	{ "-v", 0, OPT_VERSION },
	{ "-h", 0, OPT_HELP },
	{ "-l", 0, OPT_LIST },
	{ "-a", 1, OPT_APPEND },
	{ "-o", 1, OPT_OUTPUT },
	{ "-x", 0, OPT_EXTRACT },
	{ NULL, 0, OPT_UNKONWN }
};

static cmd_t cmds[] = {
	{ CMD_VERSION, cmd_version},
	{ CMD_HELP, cmd_help },
	{ CMD_LIST, cmd_list },
	{ CMD_EXTRACT, cmd_extract },
	{ CMD_APPEND, cmd_append },
	{ CMD_NONE, NULL }
};

static void opt_to_default(option_t *opt) {
	opt->cmd = CMD_NONE;
	opt->exe = NULL;
	opt->append = NULL;
	opt->output = NULL;
	opt->extract = NULL;
	opt->version = 0;
	opt->help = 0;
}

int collectargs(int argc, char **argv, option_t *opt) {
	opt_to_default(opt);
	for (int i = 1; i < argc; i++) {
		char *arg = argv[i];
		size_t len = strlen(arg);
		if (!opt->exe && len >= 4 && strcmp(arg + len - 4, ".exe") == 0) {
			opt->exe = arg;
			continue;
		}
		bool found = false;
		for (int j = 0; options[j].name; j++) {
			if (strcmp(arg, options[j].name) == 0) {
				found = true;
				if (!options[j].args) {
					switch (options[j].id) {
						case OPT_VERSION:
							opt->version = true;
							break;
						case OPT_HELP:
							opt->help = true;
							break;
						case OPT_LIST:
							opt->list = true;
							break;
						case OPT_EXTRACT:
							opt->extract = true;
						default:
							break;
					}
				}
				else {
					if (i + 1 < argc) {
						switch (options[j].id) {
							case OPT_APPEND:
								opt->append = argv[++i];
								break;
							case OPT_OUTPUT:
								opt->output = argv[++i];
								break;
							default:
								break;
						}
					}
					else {
						errprintf("Error: %s requires an argument\n", options[j].name);
					}
				}
				break;
			}
		}
		if (!found) {
			errprintf("Unknow option: %s\n", arg);
		}
	}
	return 0;
}

int set_cmd(option_t *opt) {
	int n = 0;
	if (opt->version == true) {
		opt->cmd |= CMD_VERSION;
		n++;
	}
	if (opt->help == true) {
		opt->cmd |= CMD_HELP;
		n++;
	}
	if (opt->list == true) {
		opt->cmd |= CMD_LIST;
		n++;
	}
	if (opt->extract) {
		opt->cmd |= CMD_EXTRACT;
		n++;
	}
	if (opt->exe && opt->append) {
		opt->cmd |= CMD_APPEND;
		n++;
	}
	return n;
}

int run_cmd(option_t *opt) {
	int n = 0;
	opt_cmd cmd = opt->cmd;
	for (int i = 0; cmds[i].cmd_id && cmds[i].cmd_func; i++) {
		if (opt->cmd & cmds[i].cmd_id) {
			cmds[i].cmd_func(opt);
			n++;
		}
	}
	return n;
}
