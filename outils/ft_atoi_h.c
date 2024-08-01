/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_h.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:30:53 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/01 17:29:38 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if ((unsigned char)c == '\0')
		return ((char *)s + ft_strlen(s));
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}

int	check_number(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

void	check_sin(const char *str, int *i, int *s)
{
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			*s *= -1;
		(*i)++;
	}
}

long	ft_atoi(const char *str, t_var *var)
{
	int				i;
	unsigned long	f;
	int				s;

	i = 0;
	f = 0;
	s = 1;
	if (check_number(str) == 0)
	{
		var->fil = ft_strdup("11");
		return (0);
	}
	check_sin(str, &i, &s);
	while (str[i] >= '0' && str[i] <= '9')
	{
		f = (f * 10) + str[i] - '0';
		if (f >= 9223372036854775807 && s == 1)
			return ((var->fil = ft_strdup("-1")), -1);
		if (f > 9223372036854775808UL && s == -1)
			return ((var->fil = ft_strdup("-1")), -1);
		i++;
	}
	return ((long)f * s);
}
