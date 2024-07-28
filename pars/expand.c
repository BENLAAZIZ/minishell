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
			|| line[i] == '$' || line[i] == ' ' || line[i] == '|'
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

char	*copy_the_r(t_word *token, t_env **envirment, int *sign, int old_i)
{
	char	*no_expand;
	int		length;
	char	*new;

	if (!token || !token->value)
		return (NULL);
	if (token->value[(*envirment)->i] == '$'
		&& token->value[(*envirment)->i + 1] == '"')
		(*envirment)->i += 2;
	length = dollar_length(token, envirment);
	if (length % 2 != 0)
		(*envirment)->i = (*envirment)->i - 1;
	if (token->value[(*envirment)->i] == '"' && *sign == 0)
		(*envirment)->i++;
	if (token->value[(*envirment)->i] == '$'
		&& token->value[(*envirment)->i + 1] == '\0')
		(*envirment)->i++;
	no_expand = ft_substr(token->value, old_i, (*envirment)->i - old_i);
	if (no_expand == NULL)
		return (NULL);
	new = ft_strjoin((*envirment)->expansion, no_expand);
	free((*envirment)->expansion);
	(*envirment)->expansion = new;
	// printf("5 : %s\n", (*envirment)->value);
	return ((*envirment)->expansion);
}

char	*copy_the_rest(t_word *token, t_env *envirment, int *sign)
{
	int		old_i;
	char	*rest;
	int		length;

	rest = NULL;
	old_i = envirment->i;
	length = dollar_length(token, &envirment);
	if (length % 2 != 0)
		envirment->i = envirment->i - 1;
	if (token->value[envirment->i] == '$'
		&& token->value[envirment->i + 1] == '"')
		envirment->i++;
	while (token->value[envirment->i])
	{
		ft_check_quotes(token->value[envirment->i], sign);
		if (char_stop(token, &envirment) == 1 && *sign != 1)
		{
			if (token->value[envirment->i] != '\0'
				|| check_char_expand(token->value[envirment->i + 1]) == 1)
				break ;
		}
		envirment->i++;
	}
	rest = copy_the_r(token, &envirment, sign, old_i);
	if (rest == NULL)
		return (NULL);
	// printf("4 : %s\n", envirment->value);
	return (envirment->expansion);
}

char	*copy_in_sub(t_word *token, t_env *env, int *sign, t_variable *varr)
{
	int		old_i;
	char	*no_expand;
	char	*new;

	if (env->expansion == NULL)
		env->expansion = ft_substr(token->value, 0, env->i - 2);
	if (token->value[env->i - 1] == '0')
		env->expansion = ft_strjoin(env->expansion, "minishell");
	if (token->value[env->i - 1] == '?')
		env->expansion = ft_strjoin(env->expansion, ft_itoa(varr->var.status));
	old_i = env->i;
	while (check_char_expand(token->value[env->i]) == 1 && *sign != 1)
	{
		ft_check_quotes(token->value[env->i], sign);
		if (token->value[env->i] == '$')
			break ;
		env->i++;
	}
	no_expand = ft_substr(token->value, old_i, env->i - old_i);
	if (no_expand == NULL)
		return (NULL);
	new = ft_strjoin(env->expansion, no_expand);
	free(env->expansion);
	env->expansion = new;
	free(no_expand);
	env->expansion = copy_the_rest(token, env, sign);
	// printf("3 : %s\n", env->value);
	return (env->expansion);
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

void ft_add_q(t_env **env_node)
{
	(*env_node)->value[0] *= -1;
	(*env_node)->value[ft_strlen((*env_node)->value) - 1] *= -1;
}

char	*replace(t_word *token, t_env *envirment, t_env *env_node, int *sign)
{
	char	*new;
	int		old_i;
	token->old_word = NULL;
	new = NULL;
	old_i = envirment->i;
	if (envirment->expansion == NULL)
		envirment->expansion = ft_substr(token->value, 0, envirment->i - 1);
	if (env_node != NULL && env_node->value)
	{
		if (env_node->value[0] == '\'' || env_node->value[0] == '"')
			ft_add_q(&env_node);
		new = ft_strjoin(envirment->expansion, env_node->value);
		free(envirment->expansion);
		envirment->expansion = new;
	}
	while (check_char_expand(token->value[envirment->i]) == 1 && *sign != 1)
	{
		ft_check_quotes(token->value[envirment->i], sign);
		if (token->value[envirment->i] == '$'
			|| (token->value[envirment->i] == '\'' && *sign == 1))
			break ;
		envirment->i++;
	}
	token->old_word = ft_substr(token->value, old_i - 1, envirment->i - old_i + 1);
	if (token->value[envirment->i] == '"' && *sign == 2
		&& token->value[envirment->i - 1] == '$')
		envirment->i--;
	envirment->expansion = copy_the_rest(token, envirment, sign);
	// printf("2 : %s\n", envirment->value);
	return (envirment->expansion);
}

void expand_line(t_word *token, t_env *envirment, int *sign, t_variable *varr)
{
	char	*name;
	t_env	*env_node;
	int length;

	length = dollar_length(token, &envirment);
	if ((ft_isdigit(token->value[envirment->i]) == 1)
		|| ((token->value[envirment->i] == '?')))
	{
		ft_check_quotes(token->value[envirment->i], sign);
		envirment->i++;
		envirment->expansion = copy_in_sub(token, envirment, sign, varr);
	}
	else if (length % 2 != 0 && *sign != 1	
		&& is_expand(token->value[envirment->i]) == 1)
	{
		name = expand_value(token->value + envirment->i);
		if (name == NULL)
			return ;
		env_node = point_node(envirment, name);
		free(name);
		envirment->expansion = replace(token, envirment, env_node, sign);
		
		if (envirment->expansion == NULL)
			return ;
	}
}

void	ft_is_expand(t_word *token, t_env *envirment, int *sign, t_variable *varr)
{
	if (token == NULL || token->value == NULL || envirment == NULL)
		return ;
	while (token->value[envirment->i])
	{
		ft_check_quotes(token->value[envirment->i], sign);
		if (token->value[envirment->i] == '$' && *sign != 1)
		{
			expand_line(token, envirment, sign, varr);
		}
		else
			envirment->i++;
	}
}

void	word_expand(t_word *token, t_env *envirment, t_variable *varr)
{
	int		sign;
	t_word	*token_tmp;
	token_tmp = token;
	if (token == NULL || token->value == NULL)
		return ;
	sign = 0;
	while (token)
	{
		token->old_word = NULL;
		envirment->expansion = NULL;
		envirment->i = 0;
		if ((token->type == 5) && token->next != NULL)
		{
			token = token->next->next;
			continue ;
		}
		ft_is_expand(token, envirment, &sign, varr);
		if (envirment->expansion != NULL)
			token->value = envirment->expansion;
		token = token->next;
	}
}