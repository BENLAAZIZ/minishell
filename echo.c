/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:44:27 by hben-laz          #+#    #+#             */
/*   Updated: 2024/06/02 22:11:39 by hben-laz         ###   ########.fr       */
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
		i++;
	}
		write(2, s, i);
}



void	echo(char **cmd)
{
	int	newline;
	int	index;
	
	newline = 1;
	index = 1;
	if (cmd[index] && (ft_strncmp(cmd[index], "-n", 2)) == 0)
	{
		newline = 0;
		index = 2;
	}
	while (cmd[index])
	{
		// printf("i:%d\n", index);
		
		ft_putstr(cmd[index]);
		if (cmd[index + 1])
			write(1, " ", 1);
		index++;
	}
	if (newline == 1)
		write(1, "\n", 1);
}

