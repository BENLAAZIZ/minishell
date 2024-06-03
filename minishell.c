#include "minishell.h"



void display_env(t_env *a)
{
    while(a)
    {
		if (a->value != NULL)
        	printf("%s=%s\n", a->variable, a->value);
        a = a->next;
    }
}


int main(int argc, char* argv[], char **ev)
{
	t_env	*env;
	char	*line = NULL;
	char	**cmd;


	(void)argc;
	(void)argv;
	ft_env(ev, &env);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break;
		add_history(line);
		rl_redisplay();
		cmd = ft_splith(line, ' ');
		if (ft_strncmp(cmd[0], "env", 4) == 0)
			display_env(env);
		else if (ft_strncmp(cmd[0], "echo", 5) == 0)
			echo(cmd);
		else if (ft_strncmp(cmd[0], "cd", 3) == 0)
			cd(cmd, &env);
		else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
			pwd();
		else if (ft_strncmp(cmd[0], "export", 7) == 0)
			display_list_export(env);
		free(line);
	}

    return 0;
}

