#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <stdio.h>


void	ft_lstclear(t_node **list)
{
	t_node	*tmp;

	if (list == NULL || (*list) == NULL)
		return ;
	tmp = (*list);
	while ((*list) != NULL)
	{
		tmp = (*list);
		(*list) = (*list)->next;
		free(tmp);
	}
	*list = NULL;
}

t_node	*ft_addlist(char *cmd, int j)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (new_node == NULL)
		return (NULL);
	new_node->command = malloc(j + 1);
	if (new_node->command == NULL)
		return (NULL);
	new_node->next = NULL;
	new_node->command = ft_split(cmd, ' ');
	new_node->redirection = NULL;
	return (new_node);
}

void	ft_lstaddback(t_node **list, t_node *new_node)
{
	t_node	*tmp;

	tmp = *list;
	if (list == NULL || new_node == NULL)
		return ;
	if (*list == NULL)
	{
		*list = new_node;
		return ;
	}
	while ((*list)->next != NULL)
	{
		(*list) = (*list)->next;
	}
	(*list)->next = new_node;
	*list = tmp;
}

int	ft_lstsize(t_node *stack_a)
{
	int	size;

	size = 0;
	if (stack_a == NULL)
		return (0);
	while (stack_a != NULL)
	{
		stack_a = stack_a->next;
		size++;
	}
	return (size);
}