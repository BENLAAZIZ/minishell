/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:28:38 by hben-laz          #+#    #+#             */
/*   Updated: 2024/06/09 22:04:16 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstnew(char *var, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (node == NULL)
		return (NULL);
	node->variable = var;
	node->value = value;
	node->next = NULL;
	return (node);
}

t_env	*ft_lstlast(t_env *lst)
{
	t_env	*last;

	if (!lst)
		return (NULL);
	last = lst;
	while (last->next)
		last = last->next;
	return (last);
}

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	if (!lst || !new)
		return ;
	if (!*lst)
	{
		(*lst) = new;
		return ;
	}
	ft_lstlast(*lst)->next = new;
}

int	size_pipe_node(t_node *a)
{
	int		size;

	if (!a)
		return (-1);
	size = 0;
	while (a)
	{
		size++;
		a = a -> next;
	}
	return (size);
}

int	size_env(t_env *a)
{
	int		size;

	if (!a)
		return (-1);
	size = 0;
	while (a)
	{
		if (a->value != NULL)
			size++;
		a = a -> next;
	}
	return (size);
}

t_env	*point_node(t_env *env, char *name)
{
	while (env)
	{
		if (ft_strncmp(env->variable, name, ft_strlen(name) + 1) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}