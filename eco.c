#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    int suppress_newline = 0;
	int indix = 0;

    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        suppress_newline = 1;
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
    if (!suppress_newline) {
        printf("\n");
    }
    return 0;
}
