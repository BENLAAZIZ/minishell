/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_list_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 16:36:00 by hben-laz          #+#    #+#             */
/*   Updated: 2024/07/13 16:36:01 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

t_word	*ft_addlist_token(char *word)
{
	t_word	*new_node;

	if (word == NULL)
		return (NULL);
	new_node = (t_word *)malloc(sizeof(t_word));
	if (new_node == NULL)
		return (NULL);
	new_node->next = NULL;
	new_node->value = word;
	if (ft_strcmp(word, "<") == 0)
		new_node->type = L_RED;
	else if (ft_strcmp(word, ">") == 0)
		new_node->type = R_RED;
	else if (ft_strcmp(word, "<<") == 0)
		new_node->type = DL_RED;
	else if (ft_strcmp(word, ">>") == 0)
		new_node->type = DR_RED;
	else if (ft_strcmp(word, "|") == 0)
		new_node->type = PIPE;
	else
		new_node->type = WORD;
	return (new_node);
}

void	ft_lstaddback_token(t_word **list, t_word*new_node)
{
	t_word	*tmp;

	tmp = *list;
	if (list == NULL || new_node == NULL)
		return ;
	if (*list == NULL)
	{
		*list = new_node;
		return ;
	}
	while ((*list)->next != NULL)
	{
		(*list) = (*list)->next;
	}
	(*list)->next = new_node;
	*list = tmp;
}