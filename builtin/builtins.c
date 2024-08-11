/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:28:45 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/11 10:29:00 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	modif_shlvl(t_env **env, t_env *new, char *var, char *val)
{
	t_env	*node;
	t_var	box;
	long	val_shlvl;
	char	*tmp;

	val_shlvl = 1;
	node = point_node(*env, "SHLVL");
	if (!node)
	{
		var = ft_strdup("SHLVL");
		val = ft_strdup("1");
		new = ft_lstnew(var, val);
		ft_lstadd_back(env, new);
	}
	else if (!node->value || (node->value[0] == '\0'))
		node->value = ft_strdup("1");
	else if (node->value[0] == '-')
		(free(node->value), (node->value = ft_strdup("0")));
	else
	{
		val_shlvl += ft_atoi(node->value, &box);
		tmp = node->value;
		node->value = ft_itoa(val_shlvl);
		free(tmp);
	}
}

int	built_functions(t_env **env, t_var *var, t_box *box)
{
	if (ft_strncmp(box->node->command[0], "env", 4) == 0)
		box->var.status = check_env(env, box);
	else if (ft_strncmp(box->node->command[0], "echo", 5) == 0)
		echo(box->node->command, 0, box);
	else if (ft_strncmp(box->node->command[0], "cd", 3) == 0)
		box->var.status = (long)cd(box->node->command, env);
	else if (ft_strncmp(box->node->command[0], "pwd", 4) == 0)
		box->var.status = (long)pwd(env);
	else if (ft_strncmp(box->node->command[0], "export", 7) == 0)
		export(env, box->node->command, 1, var);
	else if (ft_strncmp(box->node->command[0], "unset", 6) == 0)
		unset(env, box->node->command, var);
	else if (ft_strncmp(box->node->command[0], "exit", 6) == 0)
		ft_exit(box->node->command, var, env);
	else
		return (-1);
	return (0);
}
