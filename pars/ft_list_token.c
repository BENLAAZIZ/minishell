#include "minishell.h"

char	*copy_in_word(char *skip_d, t_env *envirment, int *sign)
{
	int		size;
	t_word	*word;

	size = envirment->i;
	word = NULL;
	while (ft_is_space(skip_d[envirment->i]) == 1
		&& skip_d[envirment->i])
		envirment->i++;
	while (skip_d[envirment->i])
	{
		if (*sign != 1 && end_point(skip_d[envirment->i], sign) == 0
			&& size != envirment->i)
			break ;
		ft_check_quotes(skip_d[envirment->i], sign);
		envirment->i++;
	}
	if (envirment->expansion == NULL)
		envirment->expansion = ft_substr(skip_d, size, envirment->i - size);
	return (envirment->expansion);
}

int	check_dollar_sign(char c1, char c2, char c3)
{
	if ((c1 == '$' && check_char_expand (c2) == 1)
		|| (c1 == '"' && c2 == '$' && check_char_expand(c3) == 1))
		return (1);
	return (0);
}

void	copy_tokens(char *all_command, int sign, t_env **envi, t_word **token)
{
	t_word	*word;

	word = NULL;
	if (sign == 0 && ((all_command[(*envi)->i] == '>'
				&& all_command[(*envi)->i + 1] == '>')
			|| (all_command[(*envi)->i] == '<'
				&& all_command[(*envi)->i + 1] == '<')))
	{
		(*envi)->expansion = ft_substr(all_command, (*envi)->i, 2);
		(*envi)->i += 2;
	}
	else if (sign == 0 && ((check_char(all_command[(*envi)->i])) != NULL))
	{
		(*envi)->expansion = ft_strdup((check_char(all_command[(*envi)->i])));
		(*envi)->i++;
	}
	else
		(*envi)->expansion = copy_in_word(all_command, *envi, &sign);
	if (sign == 0)
	{
		word = ft_addlist_token(ft_strdup((*envi)->expansion));
		ft_lstaddback_token(token, word);
		free((*envi)->expansion);
		(*envi)->expansion = NULL;
	}
}

t_word	*ft_list_tokn(char *all_command, t_word *token, t_env *envirment)
{
	int		sign;
	t_word	*word;

	word = NULL;
	sign = 0;
	envirment->i = 0;
	envirment->expansion = NULL;
	if (all_command == NULL)
		return (NULL);
	while (all_command[envirment->i] != '\0')
	{
		while (ft_is_space(all_command[envirment->i]) == 1
			&& all_command[envirment->i] && sign == 0)
			envirment->i++;
		if (all_command[envirment->i] == '\0')
			break ;
		copy_tokens(all_command, sign, &envirment, &token);
	}
	return (token);
}
