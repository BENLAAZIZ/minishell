/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:17:46 by hben-laz          #+#    #+#             */
/*   Updated: 2024/06/05 11:04:54 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **cmd, t_env	*env)
{
	env->fil = "hamza";
	env->status = 0;
	if (cmd[1])
	{
		if (cmd[2])
		{
			env->status = ft_atoi(cmd[1], env);
			if (ft_strncmp(env->fil, "11", 3) == 0)
				printf("minishell: exit: %s: numeric argument required\n", cmd[1]);
			else
			{	
			printf("minishell: exit: too many arguments\n");
			env->status = 1;
			return ;
			}
		}
		else if (cmd[1])
		{
			env->status = ft_atoi(cmd[1], env);
			if (ft_strncmp(env->fil, "11", 3) == 0)
				printf("minishell: exit: %s: numeric argument required\n", cmd[1]);
		}
	}
	exit((unsigned char)(env->status));
}
