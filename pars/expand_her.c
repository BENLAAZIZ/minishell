#include "minishell.h"


int	length_dollar(t_word *token, t_env **envirment)
{
	int	length;

	length = 0;
	while (token->line[(*envirment)->i] == '$')
	{
		length++;
		(*envirment)->i++;
	}
	return (length);
}
char	*add_rest(t_word *token, t_env *envirment, int *sign)
{
	int		old_i;
	char	*no_expand;

	old_i = envirment->i;
	int length = length_dollar(token, &envirment);
	if (length % 2 != 0)
		envirment->i = old_i;
	while (token->line[envirment->i])
	{
		ft_check_quotes(token->line[envirment->i], sign);
		if (char_stop(token->line[envirment->i]) == 1 && *sign != 1)
			break ;
		envirment->i++;
	}
	if (token->line[envirment->i] == '$'
		&& token->line[envirment->i + 1] == '"')
		{
			ft_check_quotes(token->line[envirment->i + 1], sign);
			envirment->i += 2;
		}
	if (token->line[envirment->i] == '"' && *sign == 0)
		envirment->i++;
	if (token->line[envirment->i] == '$'
		&& token->line[envirment->i + 1] == '\0')
		envirment->i++;
	no_expand = ft_substr(token->line, old_i, envirment->i - old_i);
	envirment->sub = ft_strjoin(envirment->sub, no_expand);
	return (envirment->sub);
}

char	*expand_copy(t_word *token, t_env *envirment, int *sign)
{
	int		old_i;
	char	*no_expand;

	if (envirment->sub == NULL)
		envirment->sub = ft_substr(token->line, 0, envirment->i - 2);
	if (token->line[envirment->i - 1] == '0')
		envirment->sub = ft_strjoin(envirment->sub, "minishell");
	old_i = envirment->i;
	while (check_char_expand(token->line[envirment->i]) == 1 && *sign != 1)
	{
		ft_check_quotes(token->line[envirment->i], sign);
		if (token->line[envirment->i] == '$')
			break ;
		envirment->i++;
	}
	no_expand = ft_substr(token->line, old_i, envirment->i - old_i);
	envirment->sub = ft_strjoin(envirment->sub, no_expand);
	envirment->sub = add_rest(token, envirment, sign);
	return (envirment->sub);
}

char	*new_value(t_word *token, t_env *envirment, t_env *env_node, int *sign)
{
	if (envirment->sub == NULL)
		envirment->sub = ft_substr(token->line, 0, envirment->i - 1);
	if (env_node != NULL)
		envirment->sub = ft_strjoin(envirment->sub, env_node->value);
	while (check_char_expand(token->line[envirment->i]) == 1 && *sign != 1)
	{
		ft_check_quotes(token->line[envirment->i], sign);
		if (token->line[envirment->i] == '$'
			|| (token->line[envirment->i] == '\'' && *sign == 1))
			break ;
		envirment->i++;
	}
	if (token->line[envirment->i] == '"' && *sign == 2
		&& token->line[envirment->i - 1] == '$')
		envirment->i--;
	envirment->sub = add_rest(token, envirment, sign);
	return (envirment->sub);
}



void	expand_it(t_word *token, t_env *envirment, int *sign)
{
	char	*name;
	t_env	*env_node;
	int		length;
	

	if (token == NULL || envirment == NULL || envirment->value == NULL)
		return ;
	envirment->i = 0;
	while (token->line[envirment->i])
	{
		ft_check_quotes(token->line[envirment->i], sign);
		if (token->line[envirment->i] == '$' && *sign != 1)
		{
			length = length_dollar(token, &envirment);
			if ((ft_isdigit(token->line[envirment->i]) == 1))
			{
				ft_check_quotes(token->line[envirment->i], sign);
				envirment->i++;
				envirment->sub = expand_copy(token, envirment, sign);
			}
			else if (length % 2 != 0 && *sign != 1
				&& is_expand(token->line[envirment->i]) == 1)
			{
				name = expand_value(token->line + envirment->i);
				env_node = point_node(envirment, name);
				envirment->sub = new_value(token, envirment, env_node, sign);
				free(name);
				if (envirment->sub == NULL)
					return ;
			}
		}
		else
			envirment->i++;
	}
}

void	expand_her (t_word *token, t_env *envirment)
{
	int		sign;
	t_word	*token_tmp;

	if (token == NULL ||token->line == NULL || envirment == NULL || envirment->value == NULL)
		return ;
	token_tmp = token;
	
	sign = 0;
	while (token_tmp)
	{
		envirment->sub = NULL;
		envirment->i = 0;
		expand_it(token_tmp, envirment, &sign);
		if (envirment->sub != NULL)
		{
			free(token_tmp->line);
			token_tmp->line = envirment->sub;
		}
		token_tmp = token_tmp->next;
	}
}