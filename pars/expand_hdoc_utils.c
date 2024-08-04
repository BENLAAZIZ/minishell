/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_hdoc_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaaraba <aaaraba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 10:47:02 by aaaraba           #+#    #+#             */
/*   Updated: 2024/08/04 13:29:50 by aaaraba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_add_q_her(t_env **env_node)
{
	(*env_node)->value[0] *= -1;
	(*env_node)->value[ft_strlen((*env_node)->value) - 1] *= -1;
}

char	*rephdoc_helper(t_word *token, t_env **env, t_env *env_node, int *sign)
{
	char	*new;

	new = NULL;
	if ((*env)->expansion == NULL)
		(*env)->expansion = ft_substr(token->line, 0, (*env)->i - 1);
	if (env_node != NULL && env_node->value)
	{
		if (env_node->value[0] == '\'' || env_node->value[0] == '"')
			ft_add_q_her(&env_node);
		new = ft_strjoin((*env)->expansion, env_node->value);
		free((*env)->expansion);
		(*env)->expansion = new;
	}
	while (check_char_expand(token->line[(*env)->i]) == 1 && *sign != 1)
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

	token->old_word = NULL;
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
		token->old_word = new_word;
		free(tmp);
	}
	if (token->line[env->i] == '"' && *sign == 2
		&& token->line[env->i - 1] == '$')
		env->i--;
	env->expansion = copy_the_rest_her(token, env, sign);
	return (env->expansion);
}
