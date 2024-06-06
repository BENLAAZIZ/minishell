/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:41:43 by hben-laz          #+#    #+#             */
/*   Updated: 2024/06/06 22:52:35 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_list_export(t_env *a)
{
	while (a)
	{
		if (!a->value)
			printf("declare -x %s\n", a->variable);
		else if (ft_strncmp(a->variable, "_", 2) == 0)
		{
			a = a->next;
			continue ;
		}
		else
			printf("declare -x %s=\"%s\"\n", a->variable, a->value);
		a = a->next;
	}
}

void	export(t_env **env , char **cmd)
{
	char	*var;
	char	*val;
	t_env	*exp;
	t_env	*node;
	int		i;
	int		egal;

	egal = 0;
	if (!cmd[1])
		display_list_export(*env);
	else
	{
			i = 1;
		while (cmd[i])
		{
			var = get_variabl(cmd[i], &egal);
			val = get_value(cmd[i]);
			if (check_special_char(var) == 0 || !var)
			{
				printf("minishell: export: `%s': not a valid identifier\n", cmd[i]);
				i++;
				continue ;
			}
			else
			{		
				node = point_node(*env, var);
				if (!node)
				{
					exp = ft_lstnew(var, val);
					ft_lstadd_back(env, exp);
				}
				else
				{
					//khasni nsayb hadi ila kant += egal= 1 +dfgdf egal=-1 
					if (egal == 1)
						node->value = ft_strjoin(node->value, val);
					else if(egal == -1)
						printf("minishell: export: `%s': not a valid identifier\n", cmd[i]);
					else
						node->value = val;
				}
			}
			i++;
		}
	}
	
}
