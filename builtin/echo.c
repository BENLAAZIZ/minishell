/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 10:28:12 by hben-laz          #+#    #+#             */
/*   Updated: 2024/06/09 11:45:13 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	write(1, s, i);
	return (0);
}

void	check_option_n(char *str, int *index, int *newline)
{
	int	i;

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
		if (str[i] == '\0')
		{
			*newline = 1;
			*index = 2;
		}
	}
}

int	echo(char **cmd)
{
	int	newline;
	int	index;
	int	i;
	i = 0;
	newline = 0;
	index = 1;
	check_option_n(cmd[index], &index, &newline);
	while (cmd[index])
	{
		printf("%s", cmd[index]);
		// ft_putstr(cmd[index]);
		if (cmd[index + 1])
			write(1, " ", 1);
		index++;
	}
	if (!newline)
		printf("\n");
	return (0);
}
