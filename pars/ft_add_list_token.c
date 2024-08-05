/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_list_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 16:36:00 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/05 10:29:01 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	token_type(char *word, t_word *new_node)
{
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
	else if (ft_strcmp(word, "&") == 0)
		new_node->type = AND;
	else if (ft_strcmp(word, "&&") == 0)
		new_node->type = DAND;
	else if (ft_strcmp(word, "(") == 0)
		new_node->type = OPAR;
	else if (ft_strcmp(word, ")") == 0)
		new_node->type = CPAR;
	else
		new_node->type = WORD;
}

t_word	*ft_addlist_token(char *word)
{
	t_word	*new_node;

	if (word == NULL)
		return (NULL);
	new_node = (t_word *)malloc(sizeof(t_word));
	if (new_node == NULL)
		return (NULL);
	new_node->next = NULL;
	new_node->old_word = NULL;
	new_node->value = word;
	new_node->line = NULL;
	new_node->split_value = NULL;
	new_node->is_expand = 0;
	new_node->val_noquotes = NULL;
	token_type(word, new_node);
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
