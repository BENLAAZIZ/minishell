/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:11:06 by aaaraba           #+#    #+#             */
/*   Updated: 2024/08/05 10:29:01 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*ft_lstaddback_cmd(t_node **list, t_node *new_node)
{
	t_node	*tmp;
	t_node	*node;

	tmp = *list;
	if (list == NULL || new_node == NULL)
		return (NULL);
	if (*list == NULL)
	{
		*list = new_node;
		node = *list;
		return (node);
	}
	while ((*list)->next != NULL)
	{
		(*list) = (*list)->next;
	}
	(*list)->next = new_node;
	node = (*list)->next;
	*list = tmp;
	return (node);
}

t_node	*ft_addnode_cmds(char **commands)
{
	t_node	*new_node;

	if (commands == NULL)
		return (NULL);
	new_node = (t_node *)malloc(sizeof(t_node));
	if (new_node == NULL)
		return (NULL);
	new_node->next = NULL;
	new_node->command = commands;
	return (new_node);
}
