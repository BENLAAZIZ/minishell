/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaaraba <aaaraba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:33:20 by aaaraba           #+#    #+#             */
/*   Updated: 2024/08/07 14:33:50 by aaaraba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstclear_token(t_word **list)
{
	t_word	*tmp;

	if (list == NULL || (*list) == NULL)
		return ;
	tmp = (*list);
	while ((*list) != NULL)
	{
		tmp = (*list);
		(*list) = (*list)->next;
		free(tmp->value);
		free(tmp->old_word);
		free(tmp->val_noquotes);
		free(tmp->line);
		free_t_split(tmp->split_value);
		tmp->val_noquotes = NULL;
		tmp->value = NULL;
		free(tmp);
	}
	*list = NULL;
}

void	ft_lstclear_red(t_red_node **list)
{
	t_red_node	*tmp;

	if (list == NULL || (*list) == NULL)
		return ;
	tmp = (*list);
	while ((*list) != NULL)
	{
		tmp = (*list);
		(*list) = (*list)->next;
		free(tmp->red);
		free(tmp->file);
		if (tmp->exp)
			free(tmp->exp);
		free(tmp);
	}
	*list = NULL;
}

void	ft_lstclear_cmd(t_node **list)
{
	t_node	*tmp;

	if (list == NULL || (*list) == NULL)
		return ;
	tmp = (*list);
	while ((*list) != NULL)
	{
		tmp = (*list);
		(*list) = (*list)->next;
		ft_lstclear_red(&tmp->red_node);
		tmp->red_node = NULL;
		free(tmp->command);
		tmp->command = NULL;
		free(tmp);
	}
	*list = NULL;
}
