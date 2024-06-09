/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:35:52 by hben-laz          #+#    #+#             */
/*   Updated: 2024/06/09 15:02:08 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_env(t_env *a)
{
	while (a)
	{
		if (a->value != NULL)
			printf("%s=%s\n", a->variable, a->value);
		a = a->next;
	}
}

void	ft_exuctute()
{
	
}	


void	ft_minishell(t_env **env, char **cmd)
{
	char	*line;
	int		size;
	t_node	*pipe_node;

	line = NULL;
	while (1)
	{
		size = 0;
		line = readline("minishell$ ");
		if (!line)
			break ;
		add_history(line);
		rl_redisplay();

		
		pipe_node = NULL;
		//get pipe_node [cmd[][], red[][]] -> [cmd[][], red[][]] -> [cmd[][], red[][]] -> [cmd[][], red[][]];
		// if (!pipe_node)
		// 	continue ;
		size = size_pipe_node(pipe_node);
		// if (size == 1)
		// {
		// 	//without fork
		// }
		// else
		// {
		// 	// fork for any pipe_node
		// }
		
		// *******************
		cmd = ft_splith(line, ' ');
		if (!cmd)
			continue ;
		if (ft_strncmp(cmd[0], "env", 4) == 0)
			display_env(*env);
		else if (ft_strncmp(cmd[0], "echo", 5) == 0)
			echo(cmd);
		else if (ft_strncmp(cmd[0], "cd", 3) == 0)
			cd(cmd, env);
		else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
			pwd();
		else if (ft_strncmp(cmd[0], "export", 7) == 0)
			export(env , cmd);
		else if (ft_strncmp(cmd[0], "unset", 6) == 0)
			unset(env, cmd);
		else if (ft_strncmp(cmd[0], "exit", 6) == 0)
			ft_exit(cmd, *env);
		else
			ft_exuctute();
		free(line);
	}
}

int	main(int argc, char *argv[], char **ev)
{
	t_env	*env;
	char	**cmd;

	(void)argc;
	(void)argv;
	cmd = NULL;
	ft_env(ev, &env);
	ft_minishell(&env, cmd);
	return (0);
}
