/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaaraba <aaaraba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:09:09 by aaaraba           #+#    #+#             */
/*   Updated: 2024/08/04 13:33:33 by aaaraba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_expand(char c)
{
	if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9')
		|| c == '_' || c == '"' || c == '\'')
		return (1);
	return (0);
}

char	*get_var(char *line)
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

void	ft_add_q(t_env **env_node)
{
	(*env_node)->value[0] *= -1;
	(*env_node)->value[ft_strlen((*env_node)->value) - 1] *= -1;
}

char	*replace_helper(t_word *token, t_env **env, t_env *env_node, int *sign)
{
	char	*new;

	new = NULL;
	if ((*env)->expansion == NULL)
		(*env)->expansion = ft_substr(token->value, 0, (*env)->i - 1);
	if (env_node != NULL && env_node->value)
	{
		if (env_node->value[0] == '\'' || env_node->value[0] == '"')
			ft_add_q(&env_node);
		new = ft_strjoin((*env)->expansion, env_node->value);
		free((*env)->expansion);
		(*env)->expansion = new;
	}
	while (check_char_expand(token->value[(*env)->i]) == 1 && *sign != 1)
	{
		ft_check_quotes(token->value[(*env)->i], sign);
		if (token->value[(*env)->i] == '$'
			|| (token->value[(*env)->i] == '\'' && *sign == 1))
			break ;
		(*env)->i++;
	}
	return ((*env)->expansion);
}

char	*replace(t_word *token, t_env *env, t_env *env_node, int *sign)
{
	int		old_i;
	char	*tmp;
	char	*new_word;

	old_i = env->i;
	env->expansion = replace_helper(token, &env, env_node, sign);
	tmp = ft_substr(token->value, old_i - 1, env->i - old_i + 1);
	if (tmp == NULL)
		return (NULL);
	if (token->old_word == NULL)
		token->old_word = tmp;
	else
	{
		new_word = ft_strjoin(token->old_word, tmp);
		free(token->old_word);
		token->old_word = new_word;
		free(tmp);
	}
	if (token->value[env->i] == '"' && *sign == 2
		&& token->value[env->i - 1] == '$')
		env->i--;
	env->expansion = copy_the_rest(token, env, sign);
	return (env->expansion);
}
