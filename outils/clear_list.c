/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:02:44 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/08 18:43:54 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstclear_env(t_env **env)
{
	t_env	*tmp;

	if (env == NULL || (*env) == NULL)
		return ;
	tmp = (*env);
	while ((*env) != NULL)
	{
		tmp = (*env);
		(*env) = (*env)->next;
		free(tmp->variable);
		free(tmp->value);
		tmp->variable = NULL;
		tmp->value = NULL;
		free(tmp);
	}
	*env = NULL;
}

void	free_data(t_box *box)
{
	if (box->data.path)
		free_t_split(box->data.path);
	if (box->data.cmd_env)
		free_t_split(box->data.cmd_env);
	if (box->line)
	{
		free(box->line);
		box->line = NULL;
	}
	box->node = box->tmp_node;
}

void	free_array_fd(t_box *box)
{
	int	l;

	l = 0;
	while (l < box->i)
	{
		close(box->array_fd[l]);
		l++;
	}
}
