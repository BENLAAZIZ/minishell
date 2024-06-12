/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:35:52 by hben-laz          #+#    #+#             */
/*   Updated: 2024/06/12 12:53:32 by hben-laz         ###   ########.fr       */
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

// void	handle_file_rederection(char **rederection, char **file, int *fd)
// {
// 	int	i;

// 	i = 0;
// 	while (rederection)
// 	{
// 		if (ft_strncmp(rederection[i], "<", 2) == 0 || ft_strncmp(rederection[i], "<<", 3) == 0)
// 		{
// 				fd[1] = open(file[i], O_RDONLY);
// 				dup2(fd[1], 1);
// 		}
// 		else if (ft_strncmp(rederection[i], ">", 2) == 0 || ft_strncmp(rederection[i], ">>", 3) == 0)
// 		{
// 			if (ft_strncmp(rederection[i], ">>", 3) == 0)
// 				fd[0] = open(file[i], O_RDWR | O_CREAT | O_APPEND, 0644);
// 			else
// 				fd[0] = open(file[i], O_RDWR | O_CREAT | O_TRUNC, 0644);
// 			dup2(fd[0], 0);
// 		}
// 		close(fd);
// 	}
// }


// int	exec_cmd(char **cmd, t_path *data)
// {
// 	char	*s;
// 	char	*comand;
// 	int		i;

// 	i = -1;
// 	s = NULL;
// 	comand = NULL;
// 	s = ft_strjoin("/", cmd[0]);
// 	if (!s)
// 		return (free_t_split(cmd), free_t_split(data->path), 0);
// 	while (data->path[++i])
// 	{
// 		comand = ft_strjoin(data->path[i], s);
// 		if (!comand)
// 			return (free(s), free_t_split(cmd), free_t_split(data->path), 0);
// 		if (access(comand, X_OK) != 0)
// 			free(comand);
// 		else
// 			break ;
// 	}
// 	free(s);
// 	free_t_split(data->path);
// 	if (execve(comand, cmd, data->cmd_env) == -1)
// 	{
// 		ft_error("command not found: ", cmd[0], 0, 0);
// 		return (0);
// 	}
// 	return (1);
// }



// void	ft_exuctute(char **cmd, t_path *data, t_var *var)
// {
// 	if (!cmd)
// 		ft_error("command not found: ", " ", 0, 0, data);
// 	if (ft_strchr(cmd[0], '/') != NULL)
// 	{
// 		if (execve(cmd[0], cmd, NULL) == -1)
// 			ft_error("no such file or directory: ", cmd[0], 0, 0);
// 	}
// 	if (data->path == NULL)
// 	{
// 		ft_error(": no such file or directory", cmd[0], 1, -1);
// 		free_t_split(cmd);
// 		exit(1);
// 	}
// 	exec_cmd(cmd, data);
// }	

void	ft_initialis_data(t_path *data, t_env *env)
{
	t_env	*poin;
	int		size;
	int		i;
	char	*tmp;
	t_env	*tp;
	
	size = 0;
	i = 0;
	tp = env;
	poin = point_node(env, "PATH");
	if (!poin)
		return ;
	char *str;
	str = poin->value;
	
	data->cmd_env = NULL;
	data->path = ft_splith(str, ':');
	size = size_env(env);
	printf("\nsize = %d\n", size);
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


void	ft_minishell(t_env **env, char **cmd)
{
	// t_node	*pipe_node;
	t_path	data;
	t_var	var;
	char	*line;
	int		size;
	// int		fd[2];
	
	int		i;
	line = NULL;
	while (1)
	{
		i = 0;
		size = 0;
		var.status = 0;
		line = readline("minishell$ ");
		if (!line)
			break ;
		add_history(line);
		rl_redisplay();
		
		// pipe_node = NULL;
		// data = NULL;
		ft_initialis_data(&data, *env);
		// printf("\n ======================= env =====================\n");
		// while (data.cmd_env[i])
		// {
		// 	printf("%s\n", data.cmd_env[i]);
		// 	i++;
		// }
		// printf("\n ======================= env =====================\n");
		// i = 0;
		// printf("\n ======================= data =====================\n");
		// while (data.path[i])
		// {
		// 	printf("%s\n", data.path[i]);
		// 	i++;
		// }
		// printf("\n ======================= path =====================\n");
		if (data.path)
			free_t_split(data.path);
		if (data.cmd_env)
			free_t_split(data.cmd_env);
		//get pipe_node [cmd[][], red[][]] -> [cmd[][], red[][]] -> [cmd[][], red[][]] -> [cmd[][], red[][]];
		// if (!pipe_node)
		// 	continue ;
		// size = size_pipe_node(pipe_node);
		// if (size == 1)
		// {
		// 	//without fork
		// 	handle_file_rederection(pipe_node->red_node, pipe_node->cmd_node, &fd);
		// 	ft_exuctute(pipe_node->cmd_node, &data);
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
		{
			display_env(*env);
			printf("\n\n exit status = %ld \n\n", var.status);
		}
		else if (ft_strncmp(cmd[0], "echo", 5) == 0)
		{
			echo(cmd);
			printf("\n\n exit status = %ld \n\n", var.status);
		}
		else if (ft_strncmp(cmd[0], "cd", 3) == 0)
		{
			var.status = cd(cmd, env);
			printf("\n\n exit status = %ld \n\n", var.status);
		}
		else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		{
			var.status = pwd();
			printf("\n\n exit status = %ld \n\n", var.status);
		}
		else if (ft_strncmp(cmd[0], "export", 7) == 0)
		{
			var.status = export(env , cmd);
			printf("\n\n exit status = %ld \n\n", var.status);
		}
		else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		{
			unset(env, cmd, &var);
			printf("\n\n exit status = %ld \n\n", var.status);
		}
		else if (ft_strncmp(cmd[0], "exit", 6) == 0)
		{
			ft_exit(cmd, &var);
			printf("\n\n exit status = %ld \n\n", var.status);
		}
		// else
		// 	ft_exuctute(cmd, &data, var);
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
