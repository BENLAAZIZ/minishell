/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:16:17 by aaaraba           #+#    #+#             */
/*   Updated: 2024/08/05 10:43:53 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	dollar_length(t_word *token, t_env **env)
{
	int	length;

	length = 0;
	while (token->value[(*env)->i] == '$')
	{
		length++;
		(*env)->i++;
	}
	return (length);
}

void	replace_var_helper(t_word *token, t_env **env, int *sign)
{
	char	*name;
	t_env	*env_node;
	char	*tmp;

	name = get_var(token->value + (*env)->i);
	if (name == NULL)
		return ;
	env_node = point_node(*env, name);
	free(name);
	tmp = (*env)->expansion;
	(*env)->expansion = replace(token, *env, env_node, sign);
	token->is_expand = 1;
	if ((*env)->expansion == NULL)
	{
		free(tmp);
		return ;
	}
}

void	replace_variable(t_word *token, t_env *env, int *sign, t_box *data)
{
	int		length;

	length = dollar_length(token, &env);
	if ((ft_isdigit(token->value[env->i]) == 1)
		|| ((token->value[env->i] == '?')))
	{
		ft_check_quotes(token->value[env->i], sign);
		env->i++;
		env->expansion = spcase_cp(token, env, sign, data);
	}
	else if (length % 2 != 0 && *sign != 1
		&& is_expand(token->value[env->i]) == 1)
	{
		replace_var_helper(token, &env, sign);
	}
}

void	contains_dollar(t_word *token, t_env *env, int *sign, t_box *data)
{
	char	*tmp;

	tmp = NULL;
	if (token == NULL || token->value == NULL || env == NULL)
		return ;
	while (token->value[env->i])
	{
		ft_check_quotes(token->value[env->i], sign);
		if (*sign == 0 && token->value[env->i] == '$'
			&& (token->value[env->i + 1] == '\''
				|| token->value[env->i + 1] == '"'))
		{
			tmp = token->value;
			token->value = ft_strdup(token->value + 1);
			free(tmp);
		}
		else if (token->value[env->i] == '$' && *sign != 1)
			replace_variable(token, env, sign, data);
		else
			env->i++;
	}
}

void	word_expand(t_word *token, t_env *env, t_box *data)
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
		env->expansion = NULL;
		env->i = 0;
		if ((token->type == 5) && token->next != NULL)
		{
			token = token->next->next;
			continue ;
		}
		contains_dollar(token, env, &sign, data);
		if (env->expansion != NULL)
		{
			free(token->value);
			token->value = env->expansion;
		}
		token = token->next;
	}
}
