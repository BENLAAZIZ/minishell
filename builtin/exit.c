/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:17:46 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/05 10:29:01 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(char **cmd, t_var *var, t_env **env)
{
	var->fil = "hamza";
	var->status = 0;
	if (cmd[1] && cmd[2])
	{
		var->status = ft_atoi(cmd[1], var);
		if (ft_strncmp(var->fil, "11", 3) == 0)
			ft_builtin_error(cmd[1], 18, 2);
		else
		{
			ft_builtin_error(cmd[1], 18, -1);
			var->status = 1;
			return ;
		}
	}
	else if (cmd[1])
	{
		var->status = ft_atoi(cmd[1], var);
		if (ft_strncmp(var->fil, "11", 3) == 0)
			ft_builtin_error(cmd[1], 18, 2);
	}
	ft_lstclear_env(env);
	exit((unsigned char)(var->status));
}
