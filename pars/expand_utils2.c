/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:15:33 by aaaraba           #+#    #+#             */
/*   Updated: 2024/08/05 10:43:53 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*copy_the_rest_2(t_word *token, t_env **env, int *sign, int old_i)
{
	char	*no_expand;
	int		length;
	char	*new;

	if (!token || !token->value)
		return (NULL);
	if (token->value[(*env)->i] == '$'
		&& token->value[(*env)->i + 1] == '"')
		(*env)->i += 2;
	length = dollar_length(token, env);
	if (length % 2 != 0)
		(*env)->i = (*env)->i - 1;
	if (token->value[(*env)->i] == '"' && *sign == 0)
		(*env)->i++;
	if (token->value[(*env)->i] == '$'
		&& token->value[(*env)->i + 1] == '\0')
		(*env)->i++;
	no_expand = ft_substr(token->value, old_i, (*env)->i - old_i);
	if (no_expand == NULL)
		return (NULL);
	new = ft_strjoin((*env)->expansion, no_expand);
	free((*env)->expansion);
	free(no_expand);
	(*env)->expansion = new;
	return ((*env)->expansion);
}

char	*copy_the_rest(t_word *token, t_env *env, int *sign)
{
	int		old_i;
	int		length;

	old_i = env->i;
	length = dollar_length(token, &env);
	if (length % 2 != 0)
		env->i = env->i - 1;
	if (token->value[env->i] == '$'
		&& token->value[env->i + 1] == '"')
		env->i++;
	while (token->value[env->i])
	{
		ft_check_quotes(token->value[env->i], sign);
		if (char_stop(token, &env) == 1 && *sign != 1)
		{
			if (token->value[env->i] == '\0'
				|| check_char_expand(token->value[env->i + 1]) == 1)
				break ;
		}
		env->i++;
	}
	if (copy_the_rest_2(token, &env, sign, old_i) == NULL)
		return (NULL);
	return (env->expansion);
}

char	*sp_case_helper(t_word *token, t_env *env, t_box *data)
{
	char	*tmp;

	tmp = env->expansion;
	if (token->value[env->i - 1] == '0')
	{
		env->expansion = ft_strjoin(env->expansion, "minishell");
		free(tmp);
	}
	if (token->value[env->i - 1] == '?')
	{
		env->expansion = ft_strjoin(env->expansion, ft_itoa(data->var.status));
		free(tmp);
	}
	return (env->expansion);
}

char	*spcase_cp(t_word *token, t_env *env, int *sign, t_box *data)
{
	int		old_i;
	char	*no_expand;
	char	*new;

	if (env->expansion == NULL)
		env->expansion = ft_substr(token->value, 0, env->i - 2);
	env->expansion = sp_case_helper(token, env, data);
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
	return (env->expansion);
}
