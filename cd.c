/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:39:55 by hben-laz          #+#    #+#             */
/*   Updated: 2024/06/03 17:06:05 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	cd(char **cmd, t_env **env)
{
	t_env	*home;
	char	*oldpwd;
	char	*pwd;
	
	oldpwd = getcwd(NULL, 0);
	if (oldpwd == NULL)
		return (perror(""));
	if (cmd[1] == NULL)
	{
		home = point_node(*env, "HOME");
		if (!home)
			return ;
		chdir(home->value);
	}
	else
	{
		if (chdir(cmd[1]) != 0)
			perror(cmd[1]);
	}
	home = point_node(*env, "OLDPWD");
	if (home)
		home->value = oldpwd;
	pwd = getcwd(NULL, 0);
	home = point_node(*env, "PWD");
	if (home)
		home->value = pwd;
}
