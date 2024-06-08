/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 10:28:12 by hben-laz          #+#    #+#             */
/*   Updated: 2024/06/08 15:27:08 by hben-laz         ###   ########.fr       */
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
		i++;
	write(1, s, i);
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
			newline = 1;
			index = 2;
		}
	}
}

void	echo(char **cmd)
{
	int	newline;
	int	index;
	int	i;

	i = 0;
	newline = 0;
	index = 1;
	// if (cmd[index] && cmd[index][0] == '-')
	// {
	// 	i++;
	// 	while (cmd[index][i])
	// 	{
	// 		if (cmd[index][i] != 'n')
	// 			break ;
	// 		i++;
	// 	}
	// 	if (cmd[index][i] == '\0')
	// 	{
	// 		newline = 1;
	// 		index = 2;
	// 	}
	// }
	while (cmd[index])
	{
		printf("%s", cmd[index]);
		if (cmd[index + 1])
			printf(" ");
		index++;
	}
	if (!newline)
		printf("\n");
}
