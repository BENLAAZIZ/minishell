/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:41:15 by hben-laz          #+#    #+#             */
/*   Updated: 2024/06/03 20:24:23 by hben-laz         ###   ########.fr       */
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

	size = ft_strlen(s1);
	tab = (char *)malloc(sizeof(char) * (size + 1));
	if (tab == NULL)
		return (NULL);
	if (size > 0)
		ft_memcpy(tab, s1, size);
	tab[size] = '\0';
	return (tab);
}

char	*get_variabl(char *line)
{
	int		i;
	char	*variable;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i] && (line[i] != '='))
		i++;
	variable = (char *)malloc(i + 1);
	if (!variable)
		return (NULL);
	i = 0;
	while (line[i])
	{
		if (line[i] == '=')
			break ;
		variable[i] = line[i];
		i++;
	}
	variable[i] = '\0';
	return (variable);
}

char	*get_value(char *line)
{
	int		i;
	int		j;
	int		t;
	char	*value;

	i = 0;
	j = 0;
	t = 0;
	if (!line)
		return (NULL);
	while (line[i] && (line[i] != '='))
		i++;
	t = i + 1;
	while (line[++i] != '\0')
		j++;
	value = (char *)malloc(j + 1);
	if (!value)
		return (NULL);
	i = 0;
	while (line[t])
		value[i++] = line[t++];
	value[i] = '\0';
	return (value);
}

t_env 	*point_node(t_env *env, char *name)
{
	while (env)
	{
		if (ft_strncmp(env->variable, name, ft_strlen(name) + 1) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	remove_variab(t_env **env, char *name)
{
	t_env	*node;
	t_env	*tmp;
	
	tmp = *env;
	node = point_node(*env, name);
	if (node == NULL)
		return ;
	while (*env)
	{
		if (ft_strncmp((*env)->next->variable, name, ft_strlen(name) + 1) == 0)
		{
			(*env)->next = (*env)->next->next;
			free(node->variable);
			free(node->value);
			free(node);
			*env = tmp;
			return ;
		}
		*env = (*env)->next;
	}
	*env = tmp;
}

void	modif_env(t_env **env)
{
	t_env	*new;
	
	if (point_node(*env, "PATH") == NULL)
	{
		new = ft_lstnew("PATH", "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
		ft_lstadd_back(env, new);	
	}
	remove_variab(env, "PWD");
	remove_variab(env, "OLDPWD");
	new = ft_lstnew("PWD", getcwd(NULL, 0));
	ft_lstadd_back(env, new);
	new = ft_lstnew("OLDPWD", NULL);
	ft_lstadd_back(env, new);
}

void	modif_SHELVL(t_env **env, t_env *new, char *var, char *val)
{
	t_env	*node;
	int		val_shlvl;
	
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
		val_shlvl += ft_atoi(node->value);
		node->value = ft_itoa(val_shlvl);
	}
}

void	ft_env(char **ev, t_env **env)
{
	char	*var;
	char	*val;
	t_env	*new;
	int		i;

	var = NULL;
	val = NULL;
	i = 0;
	while (ev[i])
	{
		var = get_variabl(ev[i]);
		val = get_value(ev[i]);
		new = ft_lstnew(var, val);
		ft_lstadd_back(env, new);
		i++;
	}
	modif_env(env);
	modif_SHELVL(env, new, var, val);
}
