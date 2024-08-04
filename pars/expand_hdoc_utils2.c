/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_hdoc_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaaraba <aaaraba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 10:47:25 by aaaraba           #+#    #+#             */
/*   Updated: 2024/08/04 13:33:33 by aaaraba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cpy_the_rest_2(t_word *token, t_env **env, int *sign, int old_i)
{
	char	*no_expand;
	int		length;
	char	*new;

	if (!token || !token->line)
		return (NULL);
	if (token->line[(*env)->i] == '$'
		&& token->line[(*env)->i + 1] == '"')
		(*env)->i += 2;
	length = dollar_length_her(token, env);
	if (length % 2 != 0)
		(*env)->i = (*env)->i - 1;
	if (token->line[(*env)->i] == '"' && *sign == 0)
		(*env)->i++;
	if (token->line[(*env)->i] == '$'
		&& token->line[(*env)->i + 1] == '\0')
		(*env)->i++;
	no_expand = ft_substr(token->line, old_i, (*env)->i - old_i);
	if (no_expand == NULL)
		return (NULL);
	new = ft_strjoin((*env)->expansion, no_expand);
	free((*env)->expansion);
	free(no_expand);
	(*env)->expansion = new;
	return ((*env)->expansion);
}

int	char_stop_her(t_word *token, t_env **env)
{
	int	length;

	length = dollar_length_her(token, env);
	if (length % 2 != 0)
	{
		(*env)->i--;
		return (1);
	}
	else if (token->line[(*env)->i] == '\0')
		return (1);
	return (0);
}

char	*copy_the_rest_her(t_word *token, t_env *env, int *sign)
{
	int		old_i;
	int		length;

	old_i = env->i;
	length = dollar_length_her(token, &env);
	if (length % 2 != 0)
		env->i = env->i - 1;
	if (token->line[env->i] == '$'
		&& token->line[env->i + 1] == '"')
		env->i++;
	while (token->line[env->i])
	{
		ft_check_quotes(token->line[env->i], sign);
		if (char_stop_her(token, &env) == 1 && *sign != 1)
		{
			if (token->line[env->i] != '\0'
				|| check_char_expand(token->line[env->i + 1]) == 1)
				break ;
		}
		env->i++;
	}
	if (cpy_the_rest_2(token, &env, sign, old_i) == NULL)
		return (NULL);
	return (env->expansion);
}

char	*sp_case_helper_hdoc(t_word *token, t_env *env)
{
	char	*tmp;

	tmp = env->expansion;
	if (token->line[env->i - 1] == '0')
	{
		env->expansion = ft_strjoin(env->expansion, "minishell");
		free(tmp);
	}
	if (token->line[env->i - 1] == '?')
	{
		env->expansion = ft_strjoin(env->expansion, ft_itoa(env->status));
		free(tmp);
	}
	return (env->expansion);
}

char	*spcase_cpy_hdoc(t_word *token, t_env *env, int *sign)
{
	int		old_i;
	char	*no_expand;
	char	*new;

	if (env->expansion == NULL)
		env->expansion = ft_substr(token->line, 0, env->i - 2);
	env->expansion = sp_case_helper_hdoc(token, env);
	old_i = env->i;
	while (check_char_expand(token->line[env->i]) == 1 && *sign != 1)
	{
		ft_check_quotes(token->line[env->i], sign);
		if (token->line[env->i] == '$')
			break ;
		env->i++;
	}
	no_expand = ft_substr(token->line, old_i, env->i - old_i);
	if (no_expand == NULL)
		return (NULL);
	new = ft_strjoin(env->expansion, no_expand);
	free(env->expansion);
	env->expansion = new;
	free(no_expand);
	env->expansion = copy_the_rest_her(token, env, sign);
	return (env->expansion);
}
