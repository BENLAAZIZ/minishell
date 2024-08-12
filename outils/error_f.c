/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:43:22 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/12 18:09:15 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_perror_h(char *error, int flag)
{
	write(2, "minishell: ", 11);
	write(2, error, ft_strlen(error));
	if (flag == CM_NF)
		write(2, ": command not found\n", 20);
	else if (flag == NO_F)
		write(2, ": No such file or directory\n", 28);
	else if (flag == IS_D)
		write(2, ": is a directory\n", 17);
	else if (flag == PRM_D)
		write(2, ": Permission denied\n", 20);
	else if (flag == OMB_R)
		write(2, ": ambiguous redirect\n", 21);
}

void	ft_builtin_erro_suit(char *error, int flag, int i)
{
	if (flag == FN && i == 3)
	{
		write(2, "minishell: .", 12);
		write(2, ": filename argument required\n", 29);
		write(2, ".: usage: . filename [arguments]\n", 33);
	}
	if (flag == UNS)
	{
		write(2, "minishell: unset: `", 19);
		write(2, error, ft_strlen(error));
		write(2, "': not a valid identifier\n", 26);
	}
	else if (flag == EXT && i == 2)
	{
		write(2, "minishell: exit: ", 17);
		write(2, error, ft_strlen(error));
		write(2, ": numeric argument required\n", 28);
	}
	else if (flag == EXT)
		write(2, "minishell: exit: too many arguments\n", 36);
}

void	ft_builtin_error(char *error, int flag, int i)
{
	if (flag == NO_F && i == 0)
	{
		write(2, "minishell: cd: ", 15);
		write(2, error, ft_strlen(error));
		write(2, ": No such file or directory\n", 28);
	}
	else if (flag == NO_F && i == 1)
	{
		write(2, "minishell: env: ", 16);
		write(2, error, ft_strlen(error));
		if (error)
			write(2, ": No such file or directory\n", 28);
		else
			write(2, "No such file or directory\n", 26);
	}
	else if (flag == NO_V)
	{
		write(2, "minishell: export: `", 20);
		write(2, error, ft_strlen(error));
		write(2, "': not a valid identifier\n", 26);
	}
	else
		ft_builtin_erro_suit(error, flag, i);
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

void	wait_function(int c, t_box *box)
{
	int	status;

	while (c--)
	{
		if (wait(&status) == box->id)
		{
			box->var.status = status;
			if (WIFEXITED(box->var.status))
				box->var.status = WEXITSTATUS(box->var.status);
			if (WIFSIGNALED(box->var.status))
			{
				if (WTERMSIG(status) == 2)
				{
					write(1, "\n", 1);
					box->var.status = 130;
				}
				else if (WTERMSIG(status) == 3)
				{
					write(2, "Quit: 3\n", 8);
					box->var.status = 131;
				}
			}
		}
	}
}
