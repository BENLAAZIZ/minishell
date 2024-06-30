/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:35:52 by hben-laz          #+#    #+#             */
/*   Updated: 2024/06/30 17:16:11 by hben-laz         ###   ########.fr       */
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

void	ft_initialis_data(t_path *data, t_env *env)
{
	t_env	*poin;
	int		size;
	int		i;
	char	*tmp;
	t_env	*tp;
	char *str;
	
	size = 0;
	i = 0;
	tp = env;
	poin = point_node(env, "PATH");
	if (!poin)
		return ;
	str = poin->value;
	data->cmd_env = NULL;
	data->path = ft_splith(str, ':');
	size = size_env(env);
	data->cmd_env = (char **)malloc(sizeof(char *) * (size + 1));
	while (env)
	{
		tmp = NULL;
		if (env->value)
		{	
			tmp = ft_strjoin(env->variable, "=");
			data->cmd_env[i] = ft_strjoin(tmp, env->value);
			i++;
		}
		free(tmp);
		env = env->next;
	}
	data->cmd_env[i] = NULL;
	env = tp;
}


int built_functions(t_env **env, t_var *var, char **cmd)
{
		if (ft_strncmp(cmd[0], "env", 4) == 0)
		{
			if (cmd[1])
			{
				printf("env: %s: No such file or directory\n", cmd[1]);
				var->status = 1;
			}
			else 
				display_env(*env);
		}
		else if (ft_strncmp(cmd[0], "echo", 5) == 0)
			echo(cmd);
		else if (ft_strncmp(cmd[0], "cd", 3) == 0)
			var->status = cd(cmd, env);
		else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
			var->status = pwd();
		else if (ft_strncmp(cmd[0], "export", 7) == 0)
			var->status = export(env , cmd);
		else if (ft_strncmp(cmd[0], "unset", 6) == 0)
			unset(env, cmd, var);
		else if (ft_strncmp(cmd[0], "exit", 6) == 0)
			ft_exit(cmd, var);
		else
			return (-1);
		return (0);
}

void	ft_minishell(t_env **env, char **cmd)
{
	t_node	*pipe_node;
	t_path	data;
	t_var	var;
	char	*line;
	int		size;
	// int		fd[2];
	int		pid;
	int		i;
	int b;
	
	line = NULL;
	while (1)
	{
		i = 0;
		// size = 0;
		var.status = 0;
		
		line = readline("mash$");
		if (!line)
			break ;
		add_history(line);
		rl_redisplay();
		
		pipe_node = NULL;
		ft_initialis_data(&data, *env);
		//get pipe_node [cmd[][], red[][]] -> [cmd[][], red[][]] -> [cmd[][], red[][]] -> [cmd[][], red[][]];
		// if (!pipe_node)
		// 	continue ;
		// size = size_pipe_node(pipe_node);
		cmd = ft_splith(line, ' ');
		if (!cmd)
			continue ;
		size = 1; // hadi ghi bach njarab node whda
		// handle_file_rederection(&pipe_node, fd);
		// printf("\nsize = %d\n", size);
		if (size == 1)
		{
			//without fork
			pid = fork();
			// pid = 0;
		b = built_functions(env, &var, cmd);

			if (b == -1 && pid == 0)
			{
				printf("\n b = %d \n", b);
				// if (pid == 0)
				// {
					printf("\nexcution her \n");
					ft_exuctute(cmd, &data, &var);
				// }
			}
			
		}
		// else
		// {
		// 	// while i < size : pipe_node = pipe_node->next -->
		// 	while (i < size)
		// 	{
				
		// 		if (pipe(fd) == -1)
		// 		{
		// 			perror("pipe fail :");
		// 			continue ;
		// 		}
		// 		pid = fork();
		// 		if (pid == -1)
		// 		{
		// 			perror("pid fail :"), close_fd(fd);
		// 			i++;
		// 			continue ;
		// 		}
		// 		else if (pid == 0 && built_functions(env, &var, cmd) == -1)
	
		// 			printf("\nexcution her  with fork\n");
		// 			// ft_exuctute(cmd, &data, &var);
		// 		i++;
		// 	}
			
		// }
		
		// else
		// {
		// 	// fork for any pipe_node
		// }
		// if (cmd)
		// 	free_t_split(cmd);
		if (data.path)
			free_t_split(data.path);
		if (data.cmd_env)
			free_t_split(data.cmd_env);
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
