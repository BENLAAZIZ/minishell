/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaaraba <aaaraba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:33:36 by aaaraba           #+#    #+#             */
/*   Updated: 2024/08/07 14:33:39 by aaaraba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	signal_hdoc(int check)
{
	static int	signal;

	if (check == 1)
		signal = 1;
	else if (check == 0)
		signal = 0;
	return (signal);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
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
