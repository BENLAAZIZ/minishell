/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:44:14 by hben-laz          #+#    #+#             */
/*   Updated: 2024/07/30 22:43:31 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_execute(char **cmd, t_path *data, t_variable *varr)
{
	if (!*cmd)
		exit(varr->var.status);
	if (!cmd)
	{
		ft_error("command not found: ", " ", 0, 0);
		varr->var.status = 127;
	}
	else if (ft_strchr(cmd[0], '/') != NULL)
	{
		if (execve(cmd[0], cmd,data->cmd_env) == -1)
		{
			ft_error("no such file or directory: ", cmd[0], 0, 0);
			varr->var.status = 127;
		}
	}
	else if (data->path == NULL)
	{
		ft_error(": no such file or directory", cmd[0], 1, -1);
		free_t_split(cmd);
		varr->var.status = 127;
	}
	else if (exec_cmd(cmd, data) == 0)
		varr->var.status = 127;
	exit(varr->var.status);
}
