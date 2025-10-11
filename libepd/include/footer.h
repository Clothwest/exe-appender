#pragma once

#include "epd.h"
#include "utils.h"

#include <stdint.h>
#include <stdio.h>

#define MAGIC EPD VERSION
#define MAGIC_SIZE 9
#define MAGIC_LEN (MAGIC_SIZE - 1)

#define ENAME_SIZE (MAX_PATH - 5)
#define ENAME_LEN (ENAME_SIZE - 1)

#define FNAME_SIZE (MAX_PATH - 4)
#define FNAME_LEN (FNAME_SIZE - 1)

#define TAIL EPD "TAIL"
#define TAIL_LEN 7
#define TAIL_SIZE (TAIL_LEN + 1)

#define FT_SIZE ((foffset_t)(sizeof(footer_t)))
#define FT_FSIZE (FT_SIZE - 1)

// footer should be initialized to { 0 }

typedef struct _footer
{
	char magic[MAGIC_SIZE]; // EPD0.1.0		9	bytes
	char exename[ENAME_SIZE]; //			255	bytes
	char filename[FNAME_SIZE]; // 			256	bytes
	fsize_t payload_len; // 				8 	bytes
	char tail[TAIL_LEN + 1]; //	EPDTAIL		8	bytes
} footer_t; //						total:	536	bytes  -->  epd_fwrite 535 bytes (without last '\0')

extern char footer_exename[ENAME_SIZE];

EPD_API void set_footer(footer_t *footer, const char *exepath, const char *appendfilepath, fsize_t payload_len);
EPD_API void fread_footer(footer_t *footer, FILE *stream);
EPD_API void fwrite_footer(footer_t *footer, FILE *stream);
