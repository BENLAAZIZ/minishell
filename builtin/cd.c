/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:39:55 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/11 13:40:17 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	change_env(t_env **env, t_env *home, char *oldpwd)
{
	char	*pwd;

	home = point_node(*env, "OLDPWD");
	if (home)
		(free(home->value), home->value = oldpwd);
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		home->value = NULL;
		free(oldpwd);
		return (perror(""), 1);
	}
	home = point_node(*env, "PWD");
	if (home)
		(free(home->value), home->value = pwd);
	else
	{
		home = point_node(*env, "OLDPWD");
		if (home)
			home->value = NULL;
		return (free(pwd), free(oldpwd), 0);
	}
	return (0);
}

int	check_chdir(char *str)
{
	if (chdir(str) != 0)
	{
		ft_builtin_error(str, NO_F, 0);
		return (1);
	}
	return (0);
}

int	cd(char **cmd, t_env **env)
{
	t_env	*home;
	char	*oldpwd;

	home = NULL;
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd && cmd[1])
		return (ft_builtin_error(cmd[1], NO_F, 0), 1);
	if (cmd[1] == NULL)
	{
		home = point_node(*env, "HOME");
		if (!home)
			return (1);
		if (chdir(home->value) != 0)
			perror(home->value);
	}
	else
	{
		if (check_chdir(cmd[1]) == 1)
			return (free(oldpwd), 1);
	}
	if (change_env(env, home, oldpwd) == 1)
		return (1);
	return (0);
}
