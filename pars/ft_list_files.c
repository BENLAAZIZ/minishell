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

t_red_node	*ft_addlist_files(char *file, char *redirection, char *old_word)
{
	t_red_node	*new_node;

	if (file == NULL || redirection == NULL)
		return (NULL);
	new_node = (t_red_node *)malloc(sizeof(t_red_node));
	if (new_node == NULL)
		return (NULL);
	new_node->next = NULL;
	new_node->exp = old_word;
	new_node->expand = 0;
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

void	ft_list_file(t_word	*token, t_red_node **files, t_cmd_node *node, t_env *env)
{
	t_red_node	*file_and_red;
	t_word		*tmp;
	char		*file;
	char		*red;
	char		*old_word;
	*files = NULL;
	// exit(0);
	if (token == NULL)
		return ;
	tmp = token;
	while (token)
	{
		if (token->type == PIPE)
			break ;
		if (check_red(token->type) == 1 && token->next != NULL)
		{
			file = ft_strdup(token->next->val_noquotes);
			red = ft_strdup(token->val_noquotes);
			old_word =  ft_strdup(token->next->old_word);
			file_and_red = ft_addlist_files(file, red, old_word);
			if (!file_and_red->file ||  file_and_red->file[0] == '\0')
				file_and_red->expand = 1;
			ft_lstaddback_files(files, file_and_red);
			if (token->type == 5)
			{
				// (node)->fd_herd = dup(0);
				here_doc(token->next->value, token->next->val_noquotes, node, env);
			}
			file = NULL;
			red = NULL;
		}
		token = token->next;
	}
	token = tmp;
}
