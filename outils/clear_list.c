/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:02:44 by hben-laz          #+#    #+#             */
/*   Updated: 2024/07/31 18:21:15 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	free_data(t_variable *varr)
{
	if (varr->data.path)
		free_t_split(varr->data.path);
	if (varr->data.cmd_env)
		free_t_split(varr->data.cmd_env);
	if (varr->line)
		free(varr->line);
	varr->node = varr->tmp_node;
}
