/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_hdoc_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 10:47:02 by aaaraba           #+#    #+#             */
/*   Updated: 2024/08/14 14:59:33 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	dollar_length_her(t_word *token, t_env **env)
{
	int	length;

	length = 0;
	while (token->line[(*env)->i] == '$')
	{
		length++;
		(*env)->i++;
	}
	return (length);
}

char	*rephdoc_helper(t_word *token, t_env **env, t_env *env_node, int *sign)
{
	char	*new;

	new = NULL;
	if ((*env)->expansion == NULL)
		(*env)->expansion = ft_substr(token->line, 0, (*env)->i - 1);
	if (env_node != NULL && env_node->value)
	{
		new = ft_strjoin((*env)->expansion, env_node->value);
		free((*env)->expansion);
		(*env)->expansion = new;
	}
	while (check_char_expand(token->line[(*env)->i]) == 1)
	{
		ft_check_quotes(token->line[(*env)->i], sign);
		if (token->line[(*env)->i] == '$'
			|| (token->line[(*env)->i] == '\'' && *sign == 1))
			break ;
		(*env)->i++;
	}
	return ((*env)->expansion);
}

char	*replace_her(t_word *token, t_env *env, t_env *env_node, int *sign)
{
	int		old_i;
	char	*tmp;
	char	*new_word;

	old_i = env->i;
	env->expansion = rephdoc_helper(token, &env, env_node, sign);
	tmp = ft_substr(token->line, old_i - 1, env->i - old_i + 1);
	if (tmp == NULL)
		return (NULL);
	if (token->old_word == NULL)
		token->old_word = tmp;
	else
	{
		new_word = ft_strjoin(token->old_word, tmp);
		free(token->old_word);
		free(tmp);
		token->old_word = new_word;
	}
	if (((token->line[env->i] == '"' && *sign == 2)
			|| (token->line[env->i] == '\'' && *sign == 1))
		&& token->line[env->i - 1] == '$')
		env->i--;
	env->expansion = copy_the_rest_her(token, env, sign);
	return (env->expansion);
}
