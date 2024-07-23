#include "minishell.h"

char	*expand_value(char *line)
{
	int		i;
	char	*variable;

	i = 0;
	if (!line)
		return (NULL);
	while (check_char_expand (line[i]) == 1)
		i++;
	if (i == 0)
		return (NULL);
	variable = (char *)malloc(i + 1);
	if (variable == NULL)
		return (NULL);
	i = 0;
	while (line[i])
	{
		if (line[i] == '=' || line[i] == '"'
			|| line[i] == '$' || line[i] == ' '
			|| line[i] == '\'' || line[i] == '\0')
			break ;
		variable[i] = line[i];
		i++;
	}
	variable[i] = '\0';
	return (variable);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}
int	dollar_length(t_word *token, t_env **envirment)
{
	int	length;

	length = 0;
	while (token->value[(*envirment)->i] == '$')
	{
		length++;
		(*envirment)->i++;
	}
	return (length);
}
char	*copy_the_rest(t_word *token, t_env *envirment, int *sign)
{
	int		old_i;
	char	*no_expand;

	old_i = envirment->i;
	int length = dollar_length(token, &envirment);
	if (length % 2 != 0)
		envirment->i = old_i;
	while (token->value[envirment->i])
	{
		ft_check_quotes(token->value[envirment->i], sign);
		if (char_stop(token->value[envirment->i]) == 1 && *sign != 1)
			break ;
		envirment->i++;
	}
	if (token->value[envirment->i] == '$'
		&& token->value[envirment->i + 1] == '"')
		{
			ft_check_quotes(token->value[envirment->i + 1], sign);
			envirment->i += 2;
		}
	if (token->value[envirment->i] == '"' && *sign == 0)
		envirment->i++;
	if (token->value[envirment->i] == '$'
		&& token->value[envirment->i + 1] == '\0')
		envirment->i++;
	no_expand = ft_substr(token->value, old_i, envirment->i - old_i);
	envirment->sub = ft_strjoin(envirment->sub, no_expand);
	return (envirment->sub);
}

char	*copy_in_sub(t_word *token, t_env *envirment, int *sign, t_variable *varr)
{
	int		old_i;
	char	*no_expand;

	if (envirment->sub == NULL)
		envirment->sub = ft_substr(token->value, 0, envirment->i - 2);
	if (token->value[envirment->i - 1] == '0')
		envirment->sub = ft_strjoin(envirment->sub, "minishell");
	if (token->value[envirment->i - 1] == '?')
		envirment->sub = ft_strjoin(envirment->sub, ft_itoa(varr->var.status));
	old_i = envirment->i;
	while (check_char_expand(token->value[envirment->i]) == 1 && *sign != 1)
	{
		ft_check_quotes(token->value[envirment->i], sign);
		if (token->value[envirment->i] == '$')
			break ;
		envirment->i++;
	}
	no_expand = ft_substr(token->value, old_i, envirment->i - old_i);
	envirment->sub = ft_strjoin(envirment->sub, no_expand);
	envirment->sub = copy_the_rest(token, envirment, sign);
	return (envirment->sub);
}
int is_expand(char c)
{
	if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9')
		|| c == '_' || c == '"')
		return (1);
	return (0);
}

char	*replace(t_word *token, t_env *envirment, t_env *env_node, int *sign)
{
	if (envirment->sub == NULL)
		envirment->sub = ft_substr(token->value, 0, envirment->i - 1);
	if (env_node != NULL)
		envirment->sub = ft_strjoin(envirment->sub, env_node->value);
	while (check_char_expand(token->value[envirment->i]) == 1 && *sign != 1)
	{
		ft_check_quotes(token->value[envirment->i], sign);
		if (token->value[envirment->i] == '$'
			|| (token->value[envirment->i] == '\'' && *sign == 1))
			break ;
		envirment->i++;
	}
	if (token->value[envirment->i] == '"' && *sign == 2
		&& token->value[envirment->i - 1] == '$')
		envirment->i--;
	envirment->sub = copy_the_rest(token, envirment, sign);
	return (envirment->sub);
}



void	ft_is_expand(t_word *token, t_env *envirment, int *sign, t_variable *varr)
{
	char	*name;
	t_env	*env_node;
	int		length;

	while (token->value[envirment->i])
	{
		ft_check_quotes(token->value[envirment->i], sign);
		if (token->value[envirment->i] == '$' && *sign != 1)
		{
			length = dollar_length(token, &envirment);
			if ((ft_isdigit(token->value[envirment->i]) == 1)
				|| (token->value[envirment->i] == '?' && length % 2 != 0))
			{
				ft_check_quotes(token->value[envirment->i], sign);
				envirment->i++;
				envirment->sub = copy_in_sub(token, envirment, sign, varr);
			}
			else if (length % 2 != 0 && *sign != 1
				&& is_expand(token->value[envirment->i]) == 1)
			{
				name = expand_value(token->value + envirment->i);
				env_node = point_node(envirment, name);
				envirment->sub = replace(token, envirment, env_node, sign);
				if (envirment->sub == NULL)
					return ;
			}
		}
		else
			envirment->i++;
	}
}

void	word_expand (t_word *token, t_env *envirment, t_variable *varr)
{
	int		sign;
	t_word	*token_tmp;

	token_tmp = token;
	if (token == NULL || token->value == NULL)
		return ;
	sign = 0;
	while (token)
	{
		envirment->sub = NULL;
		envirment->i = 0;
		if ((token->type == 5) && token->next != NULL)
		{
			token = token->next->next;
			continue ;
		}
		ft_is_expand(token, envirment, &sign, varr);
		if (envirment->sub != NULL)
			token->value = envirment->sub;
		token = token->next;
	}
}