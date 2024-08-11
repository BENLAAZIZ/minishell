/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:40:43 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/11 10:27:32 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd(t_env **env)
{
	char	*s;
	t_env	*pwd;
	t_env	*oldpwd;

	s = getcwd(NULL, 0);
	if (s == NULL)
	{
		pwd = point_node(*env, "PWD");
		if (!pwd)
		{
			oldpwd = point_node(*env, "OLDPWD");
			if (!oldpwd)
				perror("");
			else
				printf("%s\n", oldpwd->value);
		}
		else
			printf("%s\n", pwd->value);
		return (0);
	}
	printf("%s\n", s);
	free(s);
	return (0);
}
