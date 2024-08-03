/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:42:15 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/03 10:59:13 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_var(t_env **env, t_env	*node, char *name)
{
	t_env	*tmp;

	tmp = *env;
	while (*env)
	{
		if (ft_strncmp((*env)->next->variable, name, ft_strlen(name) + 1) == 0)
		{
			(*env)->next = (*env)->next->next;
			free(node->variable);
			free(node->value);
			free(node);
			*env = tmp;
			return ;
		}
		*env = (*env)->next;
	}
	*env = tmp;
}

void	remove_variab(t_env **env, char *name)
{
	t_env	*node;

	if (!env || !*env)
		return ;
	node = point_node(*env, name);
	if (node == NULL)
		return ;
	if (node == *env)
	{
		(*env) = (*env)->next;
		free(node->variable);
		free(node->value);
		free(node);
		return ;
	}
	remove_var(env, node, name);
}

static int	check_special_char_unset(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if ((str[0] >= '0' && str[0] <= '9'))
			return (0);
		if ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_')
			i++;
		else
			return (0);
	}
	return (1);
}

void	unset(t_env **env, char **cmd, t_var *var)
{
	t_env	*node;
	int		i;

	i = 1;
	while (cmd[i])
	{
		if (check_special_char_unset(cmd[i]) == 0)
		{
			// printf("minishell: unset: `%s': not a valid identifier\n", cmd[i]);
			ft_builtin_error(cmd[i], 17, -1);
			var->status = 1;
			i++;
			continue ;
		}
		else
		{
			node = point_node(*env, cmd[i]);
			if (node)
			{
				remove_variab(env, cmd[i]);
			}
		}
		i++;
	}
}
