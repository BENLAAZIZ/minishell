/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_suit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:09:42 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/03 10:55:38 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	check_env(t_env **env, t_variable *varr)
{
	if (varr->node->command[1])
	{
		// printf("env: %s: No such file or directory\n",
		// 	varr->node->command[1]);
		// ft_perror_h(varr->node->command[1], NO_F);
		ft_builtin_error(varr->node->command[1], NO_F, 1);
		return (127);
	}
	else
		display_env(*env);
	return (0);
}
