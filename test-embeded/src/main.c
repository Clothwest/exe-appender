#include "epd.h"
#include "footer.h"
#include "utils.h"

#include <Windows.h>
#include <stdio.h>

int main(void)
{
	char exepath[MAX_PATH];
	GetModuleFileNameA(NULL, exepath, MAX_PATH);
	FILE *exe = epd_fopen(exepath, "rb");
	footer_t footer = { 0 };
	fread_footer(&footer, exe);
	size_t exesize = epd_fsize(exe);
}
