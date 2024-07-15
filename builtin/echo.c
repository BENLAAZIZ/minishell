/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 10:28:12 by hben-laz          #+#    #+#             */
/*   Updated: 2024/07/15 16:19:09 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

int	check_option_n(char *str, int *index, int *newline)
{
	int	i;
	int	c;

	c = 0;
	i = 0;
	if (str && str[0] == '-')
	{
		i++;
		while (str[i])
		{
			if (str[i] != 'n')
				break ;
			i++;
		}
		if (i == 1)
			return (c);
		if (str[i] == '\0')
		{
			*newline = 1;
			(*index)++;
			c = 1;
		}
	}
	return (c);
}

void	echo(char **cmd)
{
	int	newline;
	int	index;
	int	i;

	newline = 0;
	index = 1;
	i = 1;
	while (cmd[i])
	{
		if (check_option_n(cmd[index], &index, &newline) == 0)
			break ;
		i++;
	}
	index = i;
	while (cmd[index])
	{
		ft_putstr(cmd[index]);
		if (cmd[index + 1])
			write(1, " ", 1);
		index++;
	}
	fflush(stdout);
	if (!newline)
		write(1, "\n", 1);
}
