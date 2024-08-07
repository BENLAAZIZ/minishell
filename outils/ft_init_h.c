/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_h.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:04:20 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/07 12:16:19 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_initialis_data(t_box *box, t_env *env, int size, int i)
{
	t_env	*poin;
	t_env	*tp;

	box->data.path = NULL;
	box->data.cmd_env = NULL;
	box->node = NULL;
	box->token = NULL;
	box->line = NULL;
	tp = env;
	poin = point_node(env, "PATH");
	if (!poin)
		return ;
	box->data.path = ft_splith(poin->value, ':');
	size = size_env(env);
	box->data.cmd_env = (char **)malloc(sizeof(char *) * (size + 1));
	while (env)
	{
		if (env->value)
			get_cmd_env(env, &box->data, &i);
		env = env->next;
	}
	box->data.cmd_env[i] = NULL;
	env = tp;
}
