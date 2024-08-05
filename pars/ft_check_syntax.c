/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 10:49:20 by aaaraba           #+#    #+#             */
/*   Updated: 2024/08/05 10:29:01 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_quotes(char *line)
{
	int	sign;
	int	i;

	i = 0;
	sign = 0;
	while (line[i] != '\0')
	{
		ft_check_quotes(line[i], &sign);
		i++;
	}
	if (sign == 1)
		return (line = NULL, ft_puterror("'"), 1);
	if (sign == 2)
		return (line = NULL, ft_puterror("\""), 1);
	return (0);
}

int	check_red(int type)
{
	if ((type == L_RED
			|| type == R_RED
			|| type == DR_RED
			|| type == DL_RED))
	{
		return (1);
	}
	return (0);
}

int	return_error_two(t_word *token)
{
	if ((check_red(token->next->type)) == 1)
	{
		if (check_red(token->next->type) == 1
			&& check_red(token->type) == 1)
			return (ft_puterror(token->next->value), 1);
		if ((check_token(token->type)) == 1)
			return (1);
	}
	if (token->next->type == PIPE && check_red(token->type) == 1)
		return (ft_puterror("|"), 1);
	if (token->type == PIPE && check_red(token->next->type) == 1
		&& token->next->next == NULL)
		return (ft_puterror("newline"), 1);
	return (0);
}

int	check_syntax(t_word *token)
{
	t_word	*tmp;

	tmp = token;
	if (token == NULL)
		return (1);
	if (token->type == PIPE)
		return (ft_puterror("|"), 1);
	while (token != NULL)
	{
		if (return_error(token) == 1)
			return (1);
		if (token->next != NULL)
		{
			if (return_error_two(token) == 1)
				return (1);
		}
		token = token->next;
	}
	token = tmp;
	return (0);
}
