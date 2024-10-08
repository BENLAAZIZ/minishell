/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaaraba <aaaraba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:06:00 by aaaraba           #+#    #+#             */
/*   Updated: 2024/08/12 18:40:13 by aaaraba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*copy_in_word(char *skip_d, t_env *env, int *sign)
{
	int		size;
	t_word	*word;
	int		j;

	j = 0;
	size = env->i;
	word = NULL;
	env->expansion = malloc(alloc_lenght(skip_d, env->i, sign) + 1);
	if (env->expansion == NULL)
		return (NULL);
	while (ft_is_space(skip_d[env->i]) == 1
		&& skip_d[env->i])
		env->i++;
	while (skip_d[env->i])
	{
		if (*sign != 1 && end_point(skip_d[env->i], sign) == 0
			&& size != env->i)
			break ;
		ft_check_quotes(skip_d[env->i], sign);
		if (skip_d[env->i] == '$')
			copy_in_word_2(&j, skip_d, &env, sign);
		else
			env->expansion[j++] = skip_d[env->i++];
	}
	return (env->expansion[j] = '\0', env->expansion);
}

void	add_to_tokens(t_word **token, t_env *env)
{
	t_word	*word;

	word = ft_addlist_token(ft_strdup(env->expansion));
	ft_lstaddback_token(token, word);
	free(env->expansion);
	env->expansion = NULL;
}

void	copy_tokens(char *all_command, int sign, t_env **envi, t_word **token)
{
	t_word	*word;
	char	*tmp;

	tmp = (*envi)->expansion;
	word = NULL;
	if (sign == 0 && ((all_command[(*envi)->i] == '>'
				&& all_command[(*envi)->i + 1] == '>')
			|| (all_command[(*envi)->i] == '<'
				&& all_command[(*envi)->i + 1] == '<')))
	{
		(*envi)->expansion = ft_substr(all_command, (*envi)->i, 2);
		(*envi)->i += 2;
	}
	else if (sign == 0 && ((check_char(all_command[(*envi)->i])) != NULL))
	{
		(*envi)->expansion = ft_strdup((check_char(all_command[(*envi)->i])));
		(*envi)->i++;
	}
	else
		(*envi)->expansion = copy_in_word(all_command, *envi, &sign);
	free(tmp);
	if (sign == 0)
		add_to_tokens(token, *envi);
}

t_word	*ft_list_tokn(char *all_command, t_word *token, t_env *env)
{
	int		sign;
	t_word	*word;

	word = NULL;
	sign = 0;
	env->i = 0;
	env->expansion = NULL;
	if (all_command == NULL)
		return (NULL);
	while (all_command[env->i] != '\0')
	{
		while (ft_is_space(all_command[env->i]) == 1
			&& all_command[env->i] && sign == 0)
			env->i++;
		if (all_command[env->i] == '\0')
			break ;
		copy_tokens(all_command, sign, &env, &token);
	}
	return (token);
}
