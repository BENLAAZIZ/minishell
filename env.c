/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:41:15 by hben-laz          #+#    #+#             */
/*   Updated: 2024/06/03 16:50:55 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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

// void	modif_SHELVL(t_env **env)
// {
	
// }

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
	// modif_SHELVL(env);
}
