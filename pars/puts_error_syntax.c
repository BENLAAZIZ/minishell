/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puts_error_syntax.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaaraba <aaaraba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:33:24 by aaaraba           #+#    #+#             */
/*   Updated: 2024/08/09 20:58:58 by aaaraba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	return (0);
}
