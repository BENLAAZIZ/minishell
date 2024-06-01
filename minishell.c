#include "minishell.h"

int main(int ac, char* av[], char **env)
{

  	if (ac > 1 && ft_strncmp(av[1], "cd", 2) == 0)
		cd(av, env);
	else if (ac > 1 && ft_strncmp(av[1], "pwd", 3) == 0)
		pwd(av);
	else 
		echo(ac, av);
    return 0;
}