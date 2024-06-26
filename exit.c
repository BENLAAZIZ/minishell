/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:17:46 by hben-laz          #+#    #+#             */
/*   Updated: 2024/06/12 11:52:33 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **cmd, t_var *var)
{
	var->fil = "hamza";
	var->status = 0;
	if (cmd[1] && cmd[2])
	{
		var->status = ft_atoi(cmd[1], var);
		if (ft_strncmp(var->fil, "11", 3) == 0)
			printf("minishell: exit: %s: numeric argument required\n", cmd[1]);
		else
		{	
			printf("minishell: exit: too many arguments\n");
			var->status = 1;
			return ;
		}
	}
	else if (cmd[1])
	{
		var->status = ft_atoi(cmd[1], var);
		if (ft_strncmp(var->fil, "11", 3) == 0)
			printf("minishell: exit: %s: numeric argument required\n", cmd[1]);
	}
	exit((unsigned char)(var->status));
}
