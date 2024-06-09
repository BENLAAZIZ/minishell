/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:35:52 by hben-laz          #+#    #+#             */
/*   Updated: 2024/06/09 21:52:55 by hben-laz         ###   ########.fr       */
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


// void	exec_cmd(char **cmd, char **cmd_find)
// {
// 	char	*s;
// 	char	*comand;
// 	int		i;

// 	i = -1;
// 	s = NULL;
// 	comand = NULL;
// 	s = ft_strjoin("/", cmd[0]);
// 	if (!s)
// 		return (free_t_split(cmd), free_t_split(cmd_find));
// 	while (cmd_find[++i])
// 	{
// 		comand = ft_strjoin(cmd_find[i], s);
// 		if (!comand)
// 			return (free(s), free_t_split(cmd), free_t_split(cmd_find));
// 		if (access(comand, X_OK) != 0)
// 			free(comand);
// 		else
// 			break ;
// 	}
// 	free(s);
// 	free_t_split(cmd_find);
// 	if (execve(comand, cmd, NULL) == -1)
// 		ft_error("command not found: ", cmd[0], 0, 0);
// }



// void	ft_exuctute(char **cmd, t_path *data)
// {
// 		if (!cmd)
// 		ft_error("command not found: ", " ", 0, 0);
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
// 	exec_cmd(cmd, data->path);
// }	

void	ft_initialis_data(t_path **path, t_env *env)
{
	t_env	*poin;
	int		size;
	int		i;
	char	*tmp;
	
	size = 0;
	i = 0;
	poin = point_node(env, "PATH");
	if (!poin)
		return ;

	char *str;
	str = poin->value;
	tmp = NULL;
	// (*path)->path = NULL;
	// (*path)->cmd_env = NULL;
	(*path)->path = ft_splith(str, ':');
	size = size_env(env);
	(*path)->cmd_env = (char **)malloc(sizeof(char *) * size + 1);
	while (env)
	{
		if (env->value)
		{	
			tmp = ft_strjoin(env->variable, "=");
			(*path)->cmd_env[i] = ft_strjoin(tmp, env->value);
		}
		else
			(*path)->cmd_env[i] = ft_strdup(env->variable);
		free(tmp);
		i++;
		env = env->next;
	}
	(*path)->cmd_env[i] = NULL;
}


void	ft_minishell(t_env **env, char **cmd)
{
	t_node	*pipe_node;
	// t_path	*path;
	char	*line;
	int		size;
	// int		fd[2];
	
	int		i;
	line = NULL;
	while (1)
	{
		size = 0;
		i = 0;
		line = readline("minishell$ ");
		if (!line)
			break ;
		add_history(line);
		rl_redisplay();

		
		pipe_node = NULL;
		// ft_initialis_data(&path, *env);
		printf("\n ======================= env =====================\n");
		// while (path->cmd_env[i])
		// {
		// 	printf("%s\n", path->cmd_env[i]);
		// 	i++;
		// }
		printf("\n ======================= env =====================\n");
		
		//get pipe_node [cmd[][], red[][]] -> [cmd[][], red[][]] -> [cmd[][], red[][]] -> [cmd[][], red[][]];
		// if (!pipe_node)
			// continue ;
		size = size_pipe_node(pipe_node);
		// if (size == 1)
		// {
		// 	//without fork
		// 	handle_file_rederection(pipe_node->red_node, pipe_node->cmd_node, &fd);
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
		// else
		// 	ft_exuctute();
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
