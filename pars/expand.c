#include "minishell.h"

char *replace_token(t_word *token, t_env *envirment, t_env *env_node, int *sign)
{
	char *special_case;


	if (env_node == NULL)
	{
		while (check_char_expand (token->value[envirment->i]) == 1)
			envirment->i++; 
		if (envirment->sub != NULL)
			return(ft_strjoin(envirment->sub, ""));
		else
			return(ft_strdup(""));
	}
	while (token->value[envirment->i] && check_char_expand(token->value[envirment->i]) == 1 && *sign != 1)
	{
		ft_check_quotes(token->value[envirment->i], sign);
		if (token->value[envirment->i] == '$' || (token->value[envirment->i] == '\'' && *sign == 1))
			break;
		envirment->i++;
	}
	ft_check_quotes(token->value[envirment->i], sign);
	if (token->value[envirment->i] == '=' || token->value[envirment->i] == ' ')
	{
		special_case = ft_strjoin(env_node->value, token->value + envirment->i);
		envirment->sub = ft_strjoin(envirment->sub, special_case);
	}
	else if (env_node->value != NULL)
			envirment->sub = ft_strjoin(envirment->sub, env_node->value);
	if (token->value[envirment->i] == '"' || token->value[envirment->i] == '\'')
		envirment->sub = ft_strjoin(envirment->sub, token->value + envirment->i);
	return (envirment->sub);
}

int dollar_lenght(char *s)
{
	int	i;
	int	sign;

	sign = 0;
	i = 0;
	while (s[i])
	{
		ft_check_quotes(s[i], &sign);
		if (sign != 1 && (check_dollar_sign(s[i], s[i + 1], s[i + 2])) == 1)
		{
			if (s[i] == '"')
					i++;
			return (i);
		}
		i++;
	}
	return (i);
}
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
	if (!variable)
		return (NULL);
	i = 0;
	while (line[i])
	{
		if (line[i] == '=' || line[i] == '"' || line[i] == '$' || line[i] == ' ' || line[i] == '\'' || line[i] == '\0')
			break ;
		variable[i] = line[i];
		i++;
	}
	variable[i] = '\0';
	return (variable);
}
void  word_expand(t_word *token, t_env *envirment)
{
	int		sign;
	char	*name;
	t_env 	*env_node;;
	t_word *token_tmp;
	token_tmp = token;

	envirment->i = -1;
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
		while (token->value[envirment->i])
		{
			ft_check_quotes(token->value[envirment->i], &sign);
			if (sign != 1 && (check_dollar_sign(token->value[envirment->i], token->value[envirment->i + 1], token->value[envirment->i + 2])) == 1)
			{
				if (token->value[envirment->i] == '"')
					envirment->i++;
				if (envirment->sub == NULL)
					envirment->sub = ft_substr(token->value ,0, envirment->i);
				else
					envirment->sub = ft_substr(envirment->sub, 0, dollar_lenght(envirment->sub));
				if (token->value[envirment->i] == '$')
					envirment->i++;
				name = expand_value(token->value + envirment->i);
				env_node = point_node(envirment, name);
				envirment->sub = replace_token(token, envirment, env_node, &sign);
			}
			if (!(sign != 1 && (check_dollar_sign(token->value[envirment->i], token->value[envirment->i + 1], token->value[envirment->i + 2])) == 1))
				envirment->i++;
		}
		if (envirment->sub != NULL)
		{
			token->value = envirment->sub;
			envirment->sub = NULL;
		}
		token = token->next;
	}
}

