/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:44:14 by hben-laz          #+#    #+#             */
/*   Updated: 2024/07/16 17:01:40 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	handle_file_rederection(t_node	*pipe_node , int *fd)
// {
// 	int	i;
// 	t_red *red;
	
// 	red = NULL;
// 	i = 0;
// 	while (pipe_node->red_node->red)
// 	{
// 		if (ft_strncmp(pipe_node->red_node->red[i], "<", 2) == 0)
// 		{
// 				fd[1] = open("text.txt", O_RDONLY | O_CREAT);
// 				dup2(fd[1], 1);
// 		}
// 		else if (ft_strncmp(pipe_node->red_node->red[i], ">", 2) == 0 || ft_strncmp(pipe_node->red_node->red[i], ">>", 3) == 0)
// 		{
// 			if (ft_strncmp(pipe_node->red_node->red[i], ">>", 3) == 0)
// 				fd[0] = open("text.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
// 			else
// 				fd[0] = open("text.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
// 			dup2(fd[0], 0);
// 		}
// 		i++;
// 		close(*fd);
// 	}
// }

int	exec_cmd(char **cmd, t_path *data)
{
	char	*s;
	char	*comand;
	int		i;

	i = -1;
	s = NULL;
	comand = NULL;
	s = ft_strjoin("/", cmd[0]);
	if (!s)
		return (free_t_split(cmd), free_t_split(data->path), 0);
	while (data->path[++i])
	{
		comand = ft_strjoin(data->path[i], s);
		if (!comand)
			return (free(s), free_t_split(cmd), free_t_split(data->path), 0);
		if (access(comand, X_OK) != 0)
			free(comand);
		else
			break ;
	}
	free(s);
	free_t_split(data->path);
	if (execve(comand, cmd, data->cmd_env) == -1)
		return (ft_error("command not found: ", cmd[0], 0, 0), 0);
	return (1);
}


void	ft_execute(char **cmd, t_path *data, t_var *var)
{
	if (!cmd)
	{
		ft_error("command not found: ", " ", 0, 0);
		var->status = 1;
		exit(var->status);
	}
	if (ft_strchr(cmd[0], '/') != NULL)
	{
		if (execve(cmd[0], cmd, NULL) == -1)
		{
			ft_error("no such file or directory: ", cmd[0], 0, 0);
			var->status = 1;
			exit(var->status);
		}
	}
	if (data->path == NULL)
	{
		ft_error(": no such file or directory", cmd[0], 1, -1);
		free_t_split(cmd);
		var->status = 1;
		exit(var->status);
	}
	if (exec_cmd(cmd, data) == 0)
		var->status = 1;
	exit(var->status);
}
