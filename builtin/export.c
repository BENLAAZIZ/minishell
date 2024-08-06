/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:41:43 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/06 18:38:26 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_special_c(char *str)
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

	if (var == NULL || var->var == NULL)
		return ;
	node = point_node(*env, var->var);

	if (!node)
		add_to_export(env, var);
	else
	{
		if (var->egal == 1)
		{
			tmp = node->value;
			node->value = ft_strjoin(tmp, var->val);
			(free(tmp), free(var->val));
		}
		else if (var->egal == -1)
		{
			ft_builtin_error(str, NO_V, -1);
			var->status = 1;
		}
		else
			if (node->variable && var->val)
				(free(node->value), (node->value = var->val));
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
			var->egal = 0;
			var->var = get_variabl_export(cmd[i], &var->egal);
			var->val = get_value(cmd[i]);
			if (check_special_c(var->var) == 0 || !var || var->egal == -1)
			{
				(free(var->var), free(var->val));
				var->var = NULL;
				var->val = NULL;
				ft_builtin_error(cmd[i], 16, -1);
				var->status = 1;
			}
			else
				export_suit(env, var, cmd[i]);
			i++;
		}
	}
}
