/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaaraba <aaaraba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:33:12 by aaaraba           #+#    #+#             */
/*   Updated: 2024/08/11 15:48:01 by aaaraba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_red_node	*ft_addlist_files(char *file, char *redirection, char *old_word)
{
	t_red_node	*new_node;

	if (file == NULL || redirection == NULL)
		return (NULL);
	new_node = (t_red_node *)malloc(sizeof(t_red_node));
	if (new_node == NULL)
		return (NULL);
	new_node->next = NULL;
	new_node->exp = old_word;
	new_node->expand = 0;
	new_node->red = redirection;
	new_node->file = file;
	return (new_node);
}

void	ft_lstaddback_files(t_red_node **list, t_red_node *new_node)
{
	t_red_node	*tmp;

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

void	add_file_red(t_red_node **files, t_word *token)
{
	t_red_node	*file_and_red;
	char		*file;
	char		*red;
	char		*old_word;

	file = ft_strdup(token->next->val_noquotes);
	red = ft_strdup(token->val_noquotes);
	old_word = ft_strdup(token->next->old_word);
	file_and_red = ft_addlist_files(file, red, old_word);
	if (!file_and_red->file || file_and_red->file[0] == '\0')
		file_and_red->expand = 1;
	ft_lstaddback_files(files, file_and_red);
}

int	list_file(t_word *tks, t_red_node **red, t_env *env, t_box *box)
{
	t_word		*tmp;

	*red = NULL;
	if (tks == NULL)
		return (0);
	tmp = tks;
	while (tks)
	{
		if (tks->type == PIPE)
			break ;
		if (check_red(tks->type) == 1 && tks->next != NULL)
		{
			add_file_red(red, tks);
			if (tks->type == 5)
			{
				box->l = tks->next->value;
				box->l_nq = tks->next->val_noquotes;
				if (here_doc(box->tmp_node, env, box) == -1)
					return (-1);
			}
		}
		tks = tks->next;
	}
	tks = tmp;
	return (0);
}
