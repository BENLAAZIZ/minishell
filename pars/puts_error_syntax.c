/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puts_error_syntax.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaaraba <aaaraba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 10:57:29 by aaaraba           #+#    #+#             */
/*   Updated: 2024/08/04 10:59:27 by aaaraba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_puterror(char *token)
{
	int	i;

	i = 0;
	write(2, "syntax error near unexpected token `", 36);
	while (token[i])
	{
		write(2, &token[i], 1);
		i++;
	}
	write(2, "'\n", 2);
}

int	check_token(int type)
{
	if (type == L_RED)
		return (ft_puterror("<"), 1);
	else if (type == R_RED)
		return (ft_puterror(">"), 1);
	else if (type == DL_RED)
		return (ft_puterror("<<"), 1);
	else if (type == DR_RED)
		return (ft_puterror(">>"), 1);
	return (0);
}

int	return_error(t_word *token)
{
	if ((token->type == PIPE && token->next == NULL)
		|| (token->type == PIPE && token->next->type == PIPE))
		return (ft_puterror("|"), 1);
	if (check_red(token->type) == 1 && token->next == NULL)
		return (ft_puterror("newline"), 1);
	if (token->type == AND)
		return (ft_puterror("&"), 1);
	if (token->type == DAND)
		return (ft_puterror("&&"), 1);
	if (token->type == OPAR)
		return (ft_puterror("("), 1);
	if (token->type == CPAR)
		return (ft_puterror(")"), 1);
	return (0);
}
