/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:41:43 by hben-laz          #+#    #+#             */
/*   Updated: 2024/06/05 10:53:03 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_list_export(t_env *a)
{
	while (a)
	{
		printf("declare -x %s=\"%s\"\n", a->variable, a->value);
		a = a->next;
	}
}

void	export(t_env **env , char **cmd, char *line)
{
	char	*var;
	char	*val;
	t_env	*exp;

	if (!cmd[1])
		display_list_export(*env);
	else
	{
		var = get_variabl(line);
		val = get_value(line);
		exp = ft_lstnew(var, val);
		ft_lstadd_back(env, exp);
	}
}
