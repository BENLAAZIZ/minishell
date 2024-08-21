/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:33:28 by aaaraba           #+#    #+#             */
/*   Updated: 2024/08/13 11:40:31 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lenght_no_quotes(t_word *token)
{
	int	quotes;
	int	i;
	int	check;
	int	old_check;

	old_check = 0;
	i = 0;
	quotes = 0;
	check = 0;
	while (token->value[i] != '\0')
	{
		old_check = check;
		ft_check_quotes(token->value[i], &check);
		if (old_check != check)
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
		length = ft_strlen(token->value);
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
