/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:51:37 by aaaraba           #+#    #+#             */
/*   Updated: 2024/08/05 10:29:01 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lenght_no_quotes(t_word *token)
{
	int	quotes;
	int	sign;
	int	i;
	int	length;

	quotes = 0;
	sign = 0;
	i = 0;
	length = strlen(token->value);
	if (token->value[0] != '"')
	{
		if (length > 1 && token->value[length - 1] == '"')
			sign = 2;
	}
	ft_check_quotes(token->value[i], &sign);
	while (token->value[i] != '\0')
	{
		if (sign == 1 && token->value[i] == '\'')
			quotes++;
		if (sign == 2 && token->value[i] == '"')
			quotes++;
		i++;
	}
	return (quotes);
}

void	skip_quotes(t_word **token, int sign, int i, int *j)
{
	while ((*token)->value[i] != '\0')
	{
		ft_check_quotes((*token)->value[i], &sign);
		if (sign != 2 && (*token)->value[i] == '\'')
		{
			(*token)->quotes_type = 1;
			i++;
		}
		else if (sign != 1 && (*token)->value[i] == '"')
		{
			(*token)->quotes_type = 2;
			i++;
		}
		else
		{
			if ((*token)->value[i] < 0)
				(*token)->value[i] *= -1;
			(*token)->val_noquotes[*j] = (*token)->value[i];
			(*j)++;
			i++;
		}
		if ((*token)->value[i] == '\0')
			break ;
	}
}

int	remove_quotes(t_word *token, int sign, int i, int j)
{
	t_word	*tmp;
	int		length;

	tmp = token;
	length = 0;
	if (token == NULL || token->value == NULL)
		return (0);
	while (token)
	{
		length = strlen(token->value);
		i = 0;
		j = 0;
		sign = 0;
		token->val_noquotes = malloc((length - lenght_no_quotes(token)) + 1);
		if (token->val_noquotes == NULL)
			return (0);
		token->quotes_type = 0;
		skip_quotes(&token, sign, i, &j);
		token->val_noquotes[j] = '\0';
		token = token->next;
	}
	token = tmp;
	return (1);
}
