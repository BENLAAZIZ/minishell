/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_suit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:09:42 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/05 10:43:53 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	display_env(t_env *a)
{
	t_env	*tmp;

	tmp = a;
	while (a)
	{
		if (a->value != NULL)
			printf("%s=%s\n", a->variable, a->value);
		a = a->next;
	}
	a = tmp;
}

int	size_env(t_env *a)
{
	int		size;

	if (!a)
		return (-1);
	size = 0;
	while (a)
	{
		if (a->value != NULL)
			size++;
		a = a -> next;
	}
	return (size);
}

int	check_env(t_env **env, t_box *box)
{
	if (box->node->command[1])
	{
		ft_builtin_error(box->node->command[1], NO_F, 1);
		return (127);
	}
	else
		display_env(*env);
	return (0);
}

void	get_cmd_env(t_env *env, t_path *data, int *i)
{
	char	*tmp;

	tmp = ft_strjoin(env->variable, "=");
	data->cmd_env[*i] = ft_strjoin(tmp, env->value);
	free(tmp);
	(*i)++;
}
