/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_h.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaaraba <aaaraba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:30:20 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/10 10:19:57 by aaaraba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	len_nbr(int n)
{
	int	len;

	len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static int	sign(int n)
{
	int	len;

	len = 0;
	if (n < 0)
		len += len_nbr(n) + 1;
	else
		len += len_nbr(n);
	return (len);
}

char	*ft_itoa(unsigned int n)
{
	char	*string;
	int		size;
	long	l;

	if (n == 0)
		return (ft_strdup("0"));
	size = sign(n);
	string = (char *)malloc(sizeof(char) * (size + 1));
	if (string == NULL)
		return (NULL);
	string[size] = '\0';
	l = (long)n;
	while (size && l)
	{
		string[--size] = l % 10 + '0';
		l = l / 10;
	}
	return (string);
}
