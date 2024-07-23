#include "minishell.h"

char	*copy_in_word(char *skip_dollars, t_env *envirment, int *sign)
{
	int		size;
	t_word	*word;

	size = envirment->i;
	word = NULL;
	while (ft_is_space(skip_dollars[envirment->i]) == 1
		&& skip_dollars[envirment->i])
		envirment->i++;
	while (skip_dollars[envirment->i])
	{
		if (*sign != 1 && end_point(skip_dollars[envirment->i], sign) == 0
			&& size != envirment->i)
			break ;
		ft_check_quotes(skip_dollars[envirment->i], sign);
		envirment->i++;
	}
	if (envirment->sub == NULL)
		envirment->sub = ft_substr(skip_dollars, size, envirment->i - size);
	return (envirment->sub);
}

int	check_dollar_sign(char c1, char c2, char c3)
{
	if ((c1 == '$' && check_char_expand (c2) == 1)
		|| (c1 == '"' && c2 == '$' && check_char_expand(c3) == 1))
		return (1);
	return (0);
}

void	copy_tokens(char *skip_dollars, int sign, t_env **envi, t_word **token)
{
	t_word	*word;

	word = NULL;
	if (sign == 0 && ((skip_dollars[(*envi)->i] == '>'
				&& skip_dollars[(*envi)->i + 1] == '>')
			|| (skip_dollars[(*envi)->i] == '<'
				&& skip_dollars[(*envi)->i + 1] == '<')))
	{
		(*envi)->sub = ft_substr(skip_dollars, (*envi)->i, 2);
		(*envi)->i += 2;
	}
	else if (sign == 0 && ((check_char(skip_dollars[(*envi)->i])) != NULL))
	{
		(*envi)->sub = ft_strdup((check_char(skip_dollars[(*envi)->i])));
		(*envi)->i++;
	}
	else
		(*envi)->sub = copy_in_word(skip_dollars, *envi, &sign);
	if (sign == 0)
	{
		word = ft_addlist_token(ft_strdup((*envi)->sub));
		ft_lstaddback_token(token, word);
		(*envi)->sub = NULL;
	}
}

t_word	*ft_list_tokn(char *all_command, t_word *token, t_env *envirment)
{
	char	*skip_dollars;
	int		sign;
	t_word	*word;

	word = NULL;
	sign = 0;
	envirment->i = 0;
	envirment->sub = NULL;
	skip_dollars = all_command;
	if (skip_dollars == NULL)
		return (NULL);
	while (skip_dollars[envirment->i] != '\0')
	{
		while (ft_is_space(skip_dollars[envirment->i]) == 1
			&& skip_dollars[envirment->i] && sign == 0)
			envirment->i++;
		if (skip_dollars[envirment->i] == '\0')
			break ;
		copy_tokens(skip_dollars, sign, &envirment, &token);
	}
	return (token);
}
