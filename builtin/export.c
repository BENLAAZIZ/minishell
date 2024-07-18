/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:41:43 by hben-laz          #+#    #+#             */
/*   Updated: 2024/07/18 16:48:12 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_special_char_export(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (!(str[0] >= 'a' && str[0] <= 'z')
		&& !(str[0] >= 'A' && str[0] <= 'Z') && str[i] != '_')
		return (0);
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_')
			i++;
		else
			return (0);
	}
	return (1);
}

static void	add_to_export(t_env **env, t_var	*var)
{
	t_env	*exp;

	exp = ft_lstnew(var->var, var->val);
	ft_lstadd_back(env, exp);
}

void	export_suit(t_env **env, t_var	*var, char *str)
{
	t_env	*node;	
	char	*tmp;

	node = point_node(*env, var->var);
	if (!node)
		add_to_export(env, var);
	else
	{
		if (var->egal == 1)
		{
			tmp = node->value;
			node->value = ft_strjoin(tmp, var->val);
			free(tmp);
		}
		else if (var->egal == -1)
		{
			printf("minishell: export: `%s': not a valid identifier\n", str);
			var->status = 1;
		}
		else
			if (node->variable && var->val)
				node->value = var->val;
	}
}

void	export(t_env **env, char **cmd, int i, t_var *var)
{
	var->egal = 0;
	var->status = 0;
	if (!cmd[1])
		display_list_export(*env);
	else
	{
		while (cmd[i])
		{
			var->var = get_variabl_export(cmd[i], &var->egal);
			var->val = get_value(cmd[i]);
			if (check_special_char_export(var->var) == 0
				|| !var || var->egal == -1)
			{
				printf("minishell: export: `%s': not a valid identifier\n",
					cmd[i]);
				i++;
				var->status = 1;
				continue ;
			}
			else
				export_suit(env, var, cmd[i]);
			i++;
		}
	}
}
