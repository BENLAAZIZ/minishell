#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	char buf[1024];
   char *s = getcwd(buf, 1024);

	printf("%s\n", s);
    return 0;
}