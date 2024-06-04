/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:35:52 by hben-laz          #+#    #+#             */
/*   Updated: 2024/06/04 18:59:20 by hben-laz         ###   ########.fr       */
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

void	ft_minishell(t_env **env, char **cmd)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		add_history(line);
		rl_redisplay();
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
			display_list_export(*env);
		else if (ft_strncmp(cmd[0], "unset", 6) == 0)
			unset(env, cmd);
		else if (ft_strncmp(cmd[0], "exit", 6) == 0)
			ft_exit(cmd, *env);
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
