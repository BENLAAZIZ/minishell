#include "minishell.h"

void	echo()
{

}

void	cd(char **av)
{
	char	*s;
  	char	*str = "ls";
	char	**cmd = ft_split(str, " ");
	
	s = getcwd(NULL, 0);
	if (s == NULL)
		perror("");
	// /Users/hben-laz/Desktop/minishell 
	printf("%s\n", s);
	// if (argv[1] = "../")
	 chdir("/Users/hben-laz/Desktop/minishell/hamzaf");
	s = getcwd(NULL, 0);
	printf("%s\n", s);
	execve("/bin/ls", cmd, NULL);
}

int main(int ac, char* av[])
{

  	if (ac > 1 && strcmp(av[1], "cd") == 0)
		cd(av);
    return 0;
}