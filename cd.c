/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:39:55 by hben-laz          #+#    #+#             */
/*   Updated: 2024/06/02 18:40:30 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	cd(char **cmd, t_env **env)
{
	// t_env	*home;
	char	*s;
	
	s = getcwd(NULL, 0);
	if (s == NULL)
		return (perror(""));
	printf("curent : %s\n", getcwd(NULL, 0));
	if (cmd[1] == NULL)
	{
		puts("-----");
		// home = point_node(env, "HOME");
		// if (!home)
		// 	return ;
		// chdir(home->value);
		while (*env)
		{
			puts("ss");
			if (ft_strncmp((*env)->variable, "HOME", ft_strlen("HOME")) == 0)
			{
				puts("+++");
				chdir((*env)->value);
				printf("%s\n", (*env)->value);
				break ;
			}
			(*env) = (*env)->next;
		}
	}
	else
	{
		if (chdir(cmd[1]) != 0)
			perror(cmd[1]);
		printf("!curent : %s\n", getcwd(NULL, 0));
	}
	printf("curent : %s\n", getcwd(NULL, 0));
}