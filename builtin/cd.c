/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:39:55 by hben-laz          #+#    #+#             */
/*   Updated: 2024/06/05 16:38:14 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_env(t_env **env, t_env *home, char *oldpwd)
{
	char	*pwd;

	home = point_node(*env, "OLDPWD");
	if (home)
		home->value = oldpwd;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (perror(""));
	home = point_node(*env, "PWD");
	if (home)
		home->value = pwd;
}

void	cd(char **cmd, t_env **env)
{
	t_env	*home;
	char	*oldpwd;

	home = NULL;
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (perror(""));
	if (cmd[1] == NULL)
	{
		home = point_node(*env, "HOME");
		if (!home)
			return ;
		if (chdir(home->value) != 0)
			perror(home->value);
	}
	else
	{
		if (chdir(cmd[1]) != 0)
			printf("minishell: cd: %s: No such file or directory\n",cmd[1]);
	}
	change_env(env, home, oldpwd);
}
