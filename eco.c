#include "minishell.h"

int main(int argc, char* argv[])
{
    int newline = 0;
	int indix = 1;

    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        newline = 1;
        indix = 2;
    }
    while (indix < argc)
	{
		printf("%s", argv[indix]);
        if (indix < argc - 1) {
            printf(" ");
        }
		indix++;
	}
    if (!newline) {
        printf("\n");
    }
    return 0;
}
