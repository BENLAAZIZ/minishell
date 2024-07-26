#include "minishell.h"

int	lenght_files(t_word	*token)
{
	int		size;
	t_word	*tmp;

	size = 0;
	tmp = token;
	while (tmp != NULL && tmp->type != PIPE)
	{
		if (check_red(tmp->type) == 1)
			size++;
		tmp = tmp->next;
	}
	return (size);
}

t_red_node	*ft_addlist_files(char *file, char *redirection)
{
	t_red_node	*new_node;

	if (file == NULL || redirection == NULL)
		return (NULL);
	new_node = (t_red_node *)malloc(sizeof(t_red_node));
	if (new_node == NULL)
		return (NULL);
	new_node->next = NULL;
	new_node->red = redirection;
	new_node->file = file;
	return (new_node);
}

void	ft_lstaddback_files(t_red_node **list, t_red_node *new_node)
{
	t_red_node	*tmp;

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

void	ft_list_file(t_word	*token, t_red_node **files, t_cmd_node **node, t_env *envirement)
{
	char		*file;
	char		*red;
	t_red_node	*file_and_red;
	t_word		*tmp;

	if (token == NULL)
		return ;
	tmp = token;
	*files = NULL;
	while (token)
	{
		if (token->type == PIPE)
			break ;
		if (check_red(token->type) == 1 && token->next != NULL)
		{
			file = ft_strdup(token->next->val_noquotes);
			red = ft_strdup(token->val_noquotes);
			file_and_red = ft_addlist_files(file, red);
			ft_lstaddback_files(files, file_and_red);
			if (token->type == 5)
			{
				(*node)->fd_herd = dup(0);
				here_doc(token->next->value, token->next->val_noquotes, *node, envirement);
				// printf("in list redirection fd_herd = %d\n", (*node)->fd_herd);
			}
			file = NULL;
			red = NULL;
		}
		token = token->next;
	}
	token = tmp;
}
