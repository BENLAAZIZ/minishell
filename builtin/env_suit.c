/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_suit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:09:42 by hben-laz          #+#    #+#             */
/*   Updated: 2024/07/24 12:07:03 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_env(t_env *a)
{
	while (a)
	{
		if (a->value != NULL)
			printf("%s=%s\n", a->variable, a->value);
		a = a->next;
	}
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
		printf("env: %s: No such file or directory\n",
			varr->node->command[1]);
		return (127);
	}
	else
		display_env(*env);
	return (0);
}
