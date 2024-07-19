/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:28:45 by hben-laz          #+#    #+#             */
/*   Updated: 2024/07/19 20:20:49 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memcpy(void	*dst, const void *src, size_t n)
{
	unsigned char	*ptr;
	unsigned char	*c;
	size_t			i;

	i = 0;
	if (n == 0)
		return (dst);
	ptr = (unsigned char *)dst;
	c = (unsigned char *)src;
	if (ptr == NULL && c == NULL)
		return (dst);
	while (i < n)
	{
		*(ptr + i) = *(c + i);
		i++;
	}
	return (dst);
}

char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*tab;

	if (!s1)
		return (NULL);
	size = ft_strlen(s1);
	tab = (char *)malloc(sizeof(char) * (size + 1));
	if (tab == NULL)
		return (NULL);
	if (size > 0)
		ft_memcpy(tab, s1, size);
	tab[size] = '\0';
	return (tab);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*ss1;
	unsigned char	*ss2;

	i = 0;
	if (!s1)
		return (s2[i]);
	if (!s2)
		return (s1[i]);
	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	while ((ss1[i] != '\0' || ss2[i] != '\0') && (n > i))
	{
		if (ss1[i] != ss2[i])
			return (ss1[i] - ss2[i]);
		i++;
	}
	if (n == i)
		return (0);
	return (ss1[i] - ss2[i]);
}

void	modif_shlvl(t_env **env, t_env *new, char *var, char *val)
{
	t_env	*node;
	t_var	varr;
	long	val_shlvl;

	val_shlvl = 1;
	node = point_node(*env, "SHLVL");
	if (!node)
	{
		var = ft_strdup("SHLVL");
		val = ft_strdup("1");
		new = ft_lstnew(var, val);
		ft_lstadd_back(env, new);
	}
	else if (!node->value || (node->value[0] == '\0'))
		node->value = ft_strdup("1");
	else if (node->value[0] == '-')
		node->value = ft_strdup("0");
	else
	{
		val_shlvl += ft_atoi(node->value, &varr);
		node->value = ft_itoa(val_shlvl);
	}
}

int built_functions(t_env **env, t_var *var, char **cmd)
{
	if (ft_strncmp(cmd[0], "env", 4) == 0)
	{
		if (cmd[1])
		{
			printf("env: %s: No such file or directory\n", cmd[1]);
			var->status = 1;
		}
		else 
			display_env(*env);
	}
	else if (ft_strncmp(cmd[0], "echo", 5) == 0)
		echo(cmd);
	else if (ft_strncmp(cmd[0], "cd", 3) == 0)
		var->status = cd(cmd, env);
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		var->status = pwd();
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
		export(env , cmd, 1, var);
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		unset(env, cmd, var);
	else if (ft_strncmp(cmd[0], "exit", 6) == 0)
		ft_exit(cmd, var);
	else
		return (-1);
	return (0);
}