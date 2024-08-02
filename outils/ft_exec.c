/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:44:14 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/02 21:13:01 by hben-laz         ###   ########.fr       */
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
		return (close(1), close(0), ft_perror_h(cmd[0], CM_NF), 0);
	return (1);
}

int	check_is_directory(char *str, t_variable *varr)
{
	struct stat	st;

	if (stat(str, &st) == -1)
	{
		ft_perror_h(str, NO_F);
		varr->var.status = 127;
		return (-1);
	}
	else
	{
		if (S_ISDIR(st.st_mode))
		{
			ft_perror_h(str, IS_D);
			varr->var.status = 126;
			return (-1);
		}
		else if (access(str, X_OK))
		{
			ft_perror_h(str, PRM_D);
			varr->var.status = 126;
			return (-1);
		}
	}
	return (0);
}

void	ft_execute(char **cmd, t_path *data, t_variable *varr)
{
	if (!*cmd)
		exit(varr->var.status);
	if (!cmd)
		ft_perror_h(" ", CM_NF);
	else if (ft_strchr(cmd[0], '/') != NULL)
	{
		if (check_is_directory(cmd[0], varr) == -1)
			exit(varr->var.status);
		if (execve(cmd[0], cmd, data->cmd_env) == -1)
			(ft_perror_h(cmd[0], NO_F), exit(127));
	}
	else if (data->path == NULL)
		(ft_perror_h(cmd[0], NO_F), free_t_split(cmd));
	else if (exec_cmd(cmd, data) == 0)
		varr->var.status = 127;
	varr->var.status = 127;
	exit(varr->var.status);
}
