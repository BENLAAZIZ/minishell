/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:42:15 by hben-laz          #+#    #+#             */
/*   Updated: 2024/06/03 23:27:26 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_variab(t_env **env, char *name)
{
	t_env	*node;
	t_env	*tmp;

	tmp = *env;
	node = point_node(*env, name);
	if (node == NULL)
		return ;
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

int	check_special_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_')
		{
			if ((str[0] >= '0' && str[0] <= '9'))
				return (0);
		}
		else
			return (0);
		i++;
	}
	return (1);
}

void	unset(t_env **env, char **cmd)
{
	t_env	*node;
	int		i;

	i = 1;
	while (cmd[i])
	{
		if (check_special_char(cmd[i]) == 0)
		{
			printf("unset: `%s': not a valid identifier\n", cmd[i]);
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
