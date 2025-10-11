#include <stdio.h>

#define CREATE 0

void print_helloworld(void);
void create_helloworld_file(void);

int main(void)
{
#if CREATE
	create_helloworld_file();
#else
	print_helloworld();
#endif
	return 0;
}

void print_helloworld(void)
{
	printf("helloworld");
}

void create_helloworld_file(void)
{
	size_t total = 0;
	const char *str = "helloworld";
	FILE *fp = fopen("helloworld.txt", "wb");
	while (total < ((size_t)1 << 30))
	{
		size_t n = fwrite(str, 1, 11, fp);
		total += n;
	}
	fclose(fp);
}
