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


void	ft_list_file(t_word	*token, t_red_node **files)
{
	char		*file;
	char		*red;
	t_red_node	*file_and_red;
	t_word		*tmp;

	tmp = token;
	*files = NULL;
	while (token)
	{
		if (token->type == PIPE)
			break ;
		if (check_red(token->type) == 1 && token->next != NULL)
		{
			file = ft_strdup(token->next->val_noquotes);
			red = ft_strdup( token->val_noquotes);
			file_and_red = ft_addlist_files(file, red);
			ft_lstaddback_files(files, file_and_red);
			file = NULL;
			red = NULL;
		}
		token = token->next;
	}
	token = tmp;
}

//   1 2 3 4 5 6 >> 7 << 8 | 9 10 | 11 12 | > 13 6

// while (token != NULL)
// 	{
// 		i = 0;
// 		j = 0;
// 		while (token->type != PIPE && token->next != NULL)
// 		{
// 			if (check_red(token->type) == 1 && token->next != NULL)
// 			{
// 				file[j] = token->next->val_noquotes;
// 				redirection[j] = token->val_noquotes;
// 				j++;
// 				i++;
// 			}
// 			token = token->next;
// 		}
// 		file_and_red = ft_addlist_files(file, redirection);
// 		ft_lstaddback_files(&files, file_and_red);
// 		token = token->next;
// 	}

// t_red_node *tmp = files;
// while(tmp != NULL)
// {
// 	i = 0;
// 	while (tmp->file[i] && tmp->red[i])
// 	{
// 		printf(" file : %s ", tmp->file[i]);
// 		printf(" red : %s  |", tmp->red[i]);
// 		i++;
// 	}
// 	printf("\n\n");
// 	tmp = tmp->next;
// }