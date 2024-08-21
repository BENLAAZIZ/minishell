/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:44:14 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/13 16:33:10 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	check_is_directory(char *str, t_box *box)
{
	struct stat	st;

	if (stat(str, &st) == -1)
	{
		ft_perror_h(str, NO_F);
		box->var.status = 127;
		return (-1);
	}
	else
	{
		if (S_ISDIR(st.st_mode))
		{
			ft_perror_h(str, IS_D);
			box->var.status = 126;
			return (-1);
		}
		else if (access(str, X_OK))
		{
			ft_perror_h(str, PRM_D);
			box->var.status = 126;
			return (-1);
		}
	}
	return (0);
}

void	check_first_array(t_box *box, char **cmd)
{
	if (cmd[1])
	{
		ft_perror_h(cmd[1], NO_F);
		box->var.status = 1;
	}
	else
	{
		ft_builtin_error(cmd[0], FN, 3);
		box->var.status = 2;
	}
	exit(box->var.status);
}

void	ft_execute(char **cmd, t_path *data, t_box *box)
{
	if (!*cmd)
		exit(box->var.status);
	if (!cmd)
		ft_perror_h(" ", CM_NF);
	if (cmd[0][0] == '.' && cmd[0][1] == '\0')
		check_first_array(box, cmd);
	else if (ft_strchr(cmd[0], '/') != NULL)
	{
		if (check_is_directory(cmd[0], box) == -1)
			exit(box->var.status);
		if (execve(cmd[0], cmd, data->cmd_env) == -1)
			(perror("execve: "), exit(127));
	}
	else if (data->path == NULL)
		(ft_perror_h(cmd[0], NO_F), free_t_split(cmd));
	else if (exec_cmd(cmd, data) == 0)
		box->var.status = 127;
	box->var.status = 127;
	exit(box->var.status);
}
