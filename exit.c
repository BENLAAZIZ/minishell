/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:17:46 by hben-laz          #+#    #+#             */
/*   Updated: 2024/06/04 20:39:58 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **cmd, t_env	*env)
{
	int	fil;

	fil = 0;
	env->status = 0;
	if (cmd[1])
	{
		if (cmd[1])
		{
			env->status = ft_atoi(cmd[1], &fil);
			if (fil == -1)
				printf("exit\nminishell: exit: %s: numeric argument required", cmd[1]);
		}
		if (cmd[2])
		{
			printf("exit\nminishell: exit: too many arguments\n");
			env->status = 1;
			return ;
		}
	}
	exit((unsigned char)(env->status));
}
