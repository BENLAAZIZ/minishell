/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_hdoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 10:46:25 by aaaraba           #+#    #+#             */
/*   Updated: 2024/08/05 10:29:01 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rep_var_hdoc2(t_word *token, t_env **env, int *sign)
{
	char	*name;
	t_env	*env_node;
	char	*tmp;

	name = get_var(token->line + (*env)->i);
	if (name == NULL)
		return ;
	env_node = point_node((*env), name);
	free(name);
	tmp = (*env)->expansion;
	(*env)->expansion = replace_her(token, (*env), env_node, sign);
	if ((*env)->expansion == NULL)
	{
		free(tmp);
		return ;
	}
}

void	rep_var_hdoc(t_word *token, t_env *env, int *sign)
{
	int	length;

	length = dollar_length_her(token, &env);
	if ((ft_isdigit(token->line[env->i]) == 1)
		|| ((token->line[env->i] == '?')))
	{
		ft_check_quotes(token->line[env->i], sign);
		env->i++;
		env->expansion = spcase_cpy_hdoc(token, env, sign);
	}
	else if (length % 2 != 0 && *sign != 1
		&& is_expand(token->line[env->i]) == 1)
	{
		rep_var_hdoc2(token, &env, sign);
	}
}

void	contains_dollar_hdoc(t_word *token, t_env *env, int *sign)
{
	if (token == NULL || token->line == NULL || env == NULL)
		return ;
	while (token->line[env->i])
	{
		ft_check_quotes(token->line[env->i], sign);
		if (token->line[env->i] == '$' && *sign != 1)
			rep_var_hdoc(token, env, sign);
		else
			env->i++;
	}
}

void	word_expand_her(t_word *token, t_env *env)
{
	int		sign;
	t_word	*token_tmp;

	token_tmp = token;
	if (token == NULL || token->line == NULL)
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
		contains_dollar_hdoc(token, env, &sign);
		if (env->expansion != NULL)
		{
			free(token->line);
			token->line = env->expansion;
		}
		token = token->next;
	}
}
