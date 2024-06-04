/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:17:46 by hben-laz          #+#    #+#             */
/*   Updated: 2024/06/04 23:35:17 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **cmd, t_env	*env)
{

	env->fil = NULL;
	env->status = 0;
	if (cmd[1])
	{
		if (cmd[2])
		{
			printf("exit\nminishell: exit: too many arguments\n");
			env->status = 1;
			return ;
		}
		else if (cmd[1])
		{
			env->status = ft_atoi(cmd[1], env);
			if (strcmp(env->fil, "11") == 0)
			{
				printf("exit\nminishell: exit: %s: numeric argument required\n", cmd[1]);
			}
		}
	}
	exit((unsigned char)(env->status));
}
