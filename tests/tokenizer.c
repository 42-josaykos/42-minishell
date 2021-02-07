# include "../includes/msh.h"
#include <stdio.h>

void tokenizer(char *input)
{
	printf("%s\n", input);
	return ;
}

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		tokenizer(argv[1]);
	}
	else {
		printf("Usage: ./a.out <args>\n");
	}
	return (0);
}