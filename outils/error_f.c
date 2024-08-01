/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:43:22 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/01 17:28:34 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_perror_h(char *error, int flag)
{
	write(2, "minishell: ", 12);
	write(2, error, ft_strlen(error));
	if (flag == 11)
		write(2, ": command not found\n", 20);
	else if (flag == 12)
		write(2, ": No such file or directory\n", 28);
	else if (flag == 13)
		write(2, ": is a directory\n", 17);
	else if (flag == 14)
		write(2, ": Permission denied\n", 20);
	else if (flag == 15)
		write(2, ": ambiguous redirect\n", 21);
}

void	ft_error(char *s, char *flag, int i, int in)
{
	if (ft_strncmp(flag, "fail", 4) != 0 && i == 1)
	{
		write(2, flag, ft_strlen(flag));
		write(2, s, ft_strlen(s));
		write(2, "\n", 1);
		if (in == -1)
			return ;
	}
	else if (ft_strncmp(flag, "fail", 4) != 0 && i == 0)
	{
		write(2, s, ft_strlen(s));
		write(2, flag, ft_strlen(flag));
		write(2, "\n", 1);
		if (in == -1)
			return ;
	}
	else
	{
		write(2, s, ft_strlen(s));
		write(2, "\n", 1);
	}
}

void	free_t_split(char **array)
{
	int	i;

	i = 0;
	if (!array || !*array)
		return ;
	while (array && array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	wait_function(int c, t_variable *varr)
{
	int	status;

	while (c--)
	{
		if (wait(&status) == varr->id)
		{
			varr->var.status = status;
			if (WIFEXITED(varr->var.status))
				varr->var.status = WEXITSTATUS(varr->var.status);
			if (WIFSIGNALED(varr->var.status))
			{
				if (WTERMSIG(status) == 2)
				{
					write(1, "\n", 1);
					varr->var.status = 130;
				}
				else if (WTERMSIG(status) == 3)
				{
					write(2, "Quit: 3\n", 8);
					varr->var.status = 131;
				}
			}
		}
	}
}
