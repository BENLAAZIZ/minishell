/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:17:46 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/05 18:28:18 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit_helper_1(char **cmd, char **array, t_var *var)
{
	if (array[1])
	{
		ft_builtin_error(cmd[1], 18, 2);
		var->status = 255;
	}
	else
	{
		var->status = ft_atoi(array[0], var);
		if (ft_strncmp(var->fil, "11", 3) == 0)
			ft_builtin_error(cmd[1], 18, 2);
		else
		{
			ft_builtin_error(cmd[1], 18, -1);
			var->status = 1;
			return (1);
		}
	}
	return (0);
}

void	ft_exit_helper_2(char **array, char **cmd, t_var *var)
{
	if (array[1])
	{
		ft_builtin_error(cmd[1], 18, 2);
		var->status = 255;
	}
	else
	{
		var->status = ft_atoi(array[0], var);
		if (ft_strncmp(var->fil, "11", 3) == 0)
			ft_builtin_error(array[0], 18, 2);
	}
}

void	ft_exit(char **cmd, t_var *var, t_env **env)
{
	char	**array;

	var->fil = "NULL";
	var->status = 0;
	array = ft_splith(cmd[1], ' ');
	if (!array)
	{
		ft_builtin_error(cmd[1], 18, 2);
		var->status = 255;
	}
	else if (cmd[1] && cmd[2])
	{
		if (ft_exit_helper_1(cmd, array, var) == 1)
			return (free_t_split(array));
	}
	else
		ft_exit_helper_2(array, cmd, var);
	ft_lstclear_env(env);
	exit((unsigned char)(var->status));
}
