/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:30:53 by hben-laz          #+#    #+#             */
/*   Updated: 2024/06/04 20:10:23 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long	ft_atoi(const char *str, int *fil)
{
	int				i;
	unsigned long	f;
	int				s;

	i = 0;
	f = 0;
	s = 1;
	if (*(str + i) == '+' || *(str + i) == '-')
	{
		if (*(str + i) == '-')
			s *= -1;
		i++;
	}
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
		{
			*fil = -1;
			return (-1);
		}
		i++;
	}
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		f = (f * 10) + str[i] - '0';
		if (f >= 9223372036854775807 && s == 1)
			return ((*fil = -1), -1);
		if (f > 9223372036854775807 && s == -1)
			return (0);
		i++;
	}
	return ((long)f * s);
}
