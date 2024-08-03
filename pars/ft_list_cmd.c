#include "minishell.h"

t_cmd_node	*ft_lstaddback_cmd(t_cmd_node **list, t_cmd_node *new_node)
{
	t_cmd_node	*tmp;
	t_cmd_node	*node;

	tmp = *list;
	if (list == NULL || new_node == NULL)
		return (NULL);
	if (*list == NULL)
	{
		*list = new_node;
		node = *list;
		return (node);
	}
	while ((*list)->next != NULL)
	{
		(*list) = (*list)->next;
	}
	(*list)->next = new_node;
	node = (*list)->next;
	*list = tmp;
	return (node);
}

t_cmd_node	*ft_addlist_cmds(char **commands)
{
	t_cmd_node	*new_node;

	if (commands == NULL)
		return (NULL);
	new_node = (t_cmd_node *)malloc(sizeof(t_cmd_node));
	if (new_node == NULL)
		return (NULL);
	new_node->next = NULL;
	new_node->command = commands;
	return (new_node);
}

int	lenght_cmds(t_word	*token)
{
	int		size;
	t_word	*tmp;

	size = 0;
	tmp = token;
	while (tmp != NULL && tmp->type != PIPE)
	{
		if (check_red(tmp->type) == 1)
		{
			tmp = tmp->next;
			if (tmp != NULL)
				tmp = tmp->next;
		}
		else
		{
			if (tmp->is_expand == 1 && tmp->val_noquotes[0] != '\0')
				size += ft_countword(tmp->val_noquotes, ' ');
			else
				size++;
			tmp = tmp->next;
		}
	}
	return (size);
}

// char	**add_cmds_files(t_word	**token)
// {
// 	char	**cmds;
// 	int		j;
// 	int		x;

// 	if (*token == NULL)
// 		return (NULL);
// 	cmds = (char **)malloc(sizeof(char *) * (lenght_cmds(*token) + 1));
// 	if (cmds == NULL)
// 		return (NULL);
// 	j = 0;
// 	while ((*token) != NULL && (*token)->type != PIPE)
// 	{
// 		x = 0;
// 		if (check_red((*token)->type) == 1) 
// 		{
// 			*token = (*token)->next;
// 			if ((*token) != NULL)
// 				*token = (*token)->next;
// 		}
// 		else
// 		{
// 			if ((*token)->is_expand == 1 && (*token)->val_noquotes[0] != '\0')
// 			{
// 				(*token)->split_value = ft_split((*token)->val_noquotes, ' ');
// 				if ((*token)->split_value == NULL)
// 					return (NULL);
// 				while ((*token)->split_value[x] != NULL)
// 				{
// 					cmds[j] = (*token)->split_value[x];
// 					x++;
// 					j++;
// 				}
// 			}
// 			else
// 				cmds[j++] = (*token)->val_noquotes;
// 			*token = (*token)->next;
// 		}
// 		cmds[j] = NULL;
// 	}
// 	return (cmds);
// }


char	**add_cmds_files(t_word	**token)
{
	char	**cmds;
	int		j;
	int		x;

	if (*token == NULL)
		return (NULL);
	cmds = (char **)malloc(sizeof(char *) * (lenght_cmds(*token) + 1));
	if (cmds == NULL)
		return (NULL);
	j = 0;
	while ((*token) != NULL && (*token)->type != PIPE)
	{
		x = 0;
		if (check_red((*token)->type) == 1) 
		{
			*token = (*token)->next;
			if ((*token) != NULL)
				*token = (*token)->next;
		}
		else
		{
			if ((*token)->is_expand == 1)
			{
				if ((*token)->val_noquotes && (*token)->val_noquotes[0] != '\0')
				{
					(*token)->split_value = ft_split((*token)->val_noquotes, ' ');
					if ((*token)->split_value == NULL)
						return (NULL);
					while ((*token)->split_value[x] != NULL)
					{
						cmds[j] = (*token)->split_value[x];
						x++;
						j++;
					}
				}
			}
			else
				cmds[j++] = (*token)->val_noquotes;
			*token = (*token)->next;
		}
		cmds[j] = NULL;
	}
	return (cmds);
}

void	ft_list_cmd(t_word	*token, t_cmd_node **cmd, t_env *env)
{
	char		**cmds;
	t_cmd_node	*commands;
	t_word		*tmp;
	t_word		*tmp2;
	t_cmd_node	*node;

	cmds = NULL;
	commands = NULL;
	tmp2 = token;
	tmp = token;
	while (token != NULL)
	{
		cmds = add_cmds_files(&token);
		commands = ft_addlist_cmds(cmds);
		node = ft_lstaddback_cmd(cmd, commands);
		ft_list_file(tmp, &(commands->red_node), node, env);
		if (token && token->next != NULL)
		{
			token = token->next;
			tmp = token;
		}
	}
	token = tmp2;
}
