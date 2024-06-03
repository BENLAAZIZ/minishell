/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:44:27 by hben-laz          #+#    #+#             */
/*   Updated: 2024/06/03 23:23:34 by hben-laz         ###   ########.fr       */
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

void	echo(char **cmd)
{
	int	newline;
	int	index;

	newline = 0;
	index = 1;
	if (cmd[index] && (ft_strncmp(cmd[index], "-n", 3)) == 0)
	{
		newline = 1;
		index = 2;
	}
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
