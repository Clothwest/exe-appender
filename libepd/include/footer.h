#pragma once

#include "epd.h"

#include <stdint.h>
#include <stdio.h>

#define MAGIC EPD VERSION
#define MAGIC_SIZE 9
#define ENAME_LEN 64
#define FNAME_LEN (64 - MAGIC_SIZE - sizeof(uint64_t) - 1)

#define TAIL EPD "TAIL"
#define TAIL_LEN 7

#define FTSIZE ((signed long)(sizeof(footer_t) + TAIL_LEN))

#pragma pack(push, 1)
typedef struct _footer {
	char magic[MAGIC_SIZE]; // EPD0.1.0		9	bytes
	char exename[ENAME_LEN]; //				64	bytes
	char filename[FNAME_LEN + 1]; // 		47 	bytes
	uint64_t payload_len; // 				8 	bytes
} footer_t; //						total:	128	bytes
#pragma pack(pop)

EPD_API void set_footer(footer_t *footer, const char *exename, const char *appendfilename, uint64_t payload_len);
EPD_API void fwrite_footer(footer_t *footer, FILE *fp);
EPD_API void fread_footer(footer_t *footer, FILE *fp);
