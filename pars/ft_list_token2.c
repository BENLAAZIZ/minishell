/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_token2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 18:40:18 by aaaraba           #+#    #+#             */
/*   Updated: 2024/08/13 12:07:18 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	d_length(char *str, int i)
{
	int	length;

	length = 0;
	while (str[i] == '$')
	{
		i++;
		length++;
	}
	return (length);
}

void	increment_i_length(int *i, int *length)
{
	(*i)++;
	(*length)++;
}

int	alloc_lenght2(char *skip_d, int *i, int length, int length_d)
{
	int	sign;

	sign = length_d;
	length_d = d_length(skip_d, *i);
	if (length_d % 2 == 0)
	{
		while (skip_d[(*i)] == '$')
			increment_i_length(i, &length);
	}
	else
	{
		while (length_d-- > 1)
			increment_i_length(i, &length);
		if ((skip_d[*i + 1] == '"' || skip_d[*i + 1] == '\'') && sign == 0)
			(*i)++;
		else
			increment_i_length(i, &length);
	}
	return (length);
}

int	alloc_lenght(char *skip_d, int i, int *sign)
{
	int	length_d;
	int	length;
	int	size;

	size = i;
	length = 0;
	length_d = 0;
	while (skip_d[i] && (ft_is_space(skip_d[i]) == 1))
		i++;
	while (skip_d[i])
	{
		if (*sign != 1 && end_point(skip_d[i], sign) == 0
			&& size != i)
			return (length);
		ft_check_quotes(skip_d[i], sign);
		if (skip_d[i] == '$')
			length += alloc_lenght2(skip_d, &i, *sign, length_d);
		else
		{
			length++;
			i++;
		}
	}
	return (length);
}

void	copy_in_word_2(int *j, char *skip_d, t_env **env, int *sign)
{
	int	length;

	length = d_length(skip_d, (*env)->i);
	if (length % 2 == 0)
	{
		while (skip_d[(*env)->i] == '$')
			(*env)->expansion[(*j)++] = skip_d[(*env)->i++];
	}
	else
	{
		while (length-- > 1)
			(*env)->expansion[(*j)++] = skip_d[(*env)->i++];
		if ((skip_d[(*env)->i + 1] == '"'
				|| skip_d[(*env)->i + 1] == '\'') && *sign == 0)
			(*env)->i++;
		else
			(*env)->expansion[(*j)++] = skip_d[(*env)->i++];
	}
}
