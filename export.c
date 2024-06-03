/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:41:43 by hben-laz          #+#    #+#             */
/*   Updated: 2024/06/03 23:45:33 by hben-laz         ###   ########.fr       */
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
	printf("\n");
}

// void	export(t_env **env , char *line)
// {
// 	char	*var;
// 	char	*val;
// 	t_env	*node;
// 	var = get_variabl(line);
// 	val = get_value(line);
// 	node = ft_lstnew(var, val);
// 	ft_lstadd_back(env, node);
// }
