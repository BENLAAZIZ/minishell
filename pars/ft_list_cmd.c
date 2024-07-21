#include "minishell.h"

void	ft_lstaddback_cmd(t_cmd_node **list, t_cmd_node *new_node)
{
	t_cmd_node	*tmp;

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
		if (tmp->next)
		{
			if (check_red(tmp->type) == 0 && check_red(tmp->next->type) == 0)
				size++;
		}
		else
			size++;
		tmp = tmp->next;
	}
	return (size);
}


// void	desplay_red_node(t_red_node *redd)
// {
// 	if (!redd)
// 		return ;
// 	while (redd)
// 	{
// 		printf("[red = %s]", redd->red);
// 		printf("[file = %s]", redd->file);
// 		printf(" ---> ");
// 		redd = redd->next;
// 	} 
// }


// void	desplay_node(t_cmd_node *cmd)
// {
// 	int i;
// 	if (!cmd)
// 		printf("nothing\n");
// 	else
// 	{
// 		while (cmd)
// 		{
// 		printf("\n ========================================== \n\n");
// 			printf("red : ");
// 			desplay_red_node(cmd->red_node);
// 			i = 0;
// 			if (cmd->command)
// 			{
// 				while (cmd->command[i])
// 				{
// 					printf("\ncommand: %s", cmd->command[i]);
// 					i++;
// 				}
// 				puts("");
// 			}
// 			cmd = cmd->next;
// 			puts("\n\n");
// 		}
// 		printf("\n");

// 	}
// }

void	ft_list_cmd(t_word	*token, t_cmd_node **cmd)
{
	int			j;
	char		**cmds;
	t_cmd_node	*commands;
	t_word		*tmp;
	t_word		*tmp2;

	commands = (t_cmd_node *)malloc(sizeof(t_cmd_node));
	tmp2 = token;
	tmp = token;
	while (token != NULL)
	{
		cmds = (char **)malloc(sizeof(char *) * (lenght_cmds(token) + 1));
		if (cmds == NULL)
			return ;
		
		j = 0;
		while (token != NULL && token->type != PIPE)
		{
			if (check_red(token->type) == 1)
			{
				token = token->next;
				if (token != NULL)
					token = token->next;
			}
			else
			{
				cmds[j++] = token->val_noquotes;
				token = token->next;
			}
		}
		cmds[j] = NULL;
		commands = ft_addlist_cmds(cmds);
		ft_lstaddback_cmd(cmd, commands);
		ft_list_file(tmp, &(commands->red_node), &(*cmd)->fd_herd);
		dprintf(2, "herd in node = %d\n", (*cmd)->fd_herd);
		if (token && token->next != NULL)
		{
			token = token->next;
			tmp = token;
		}
	}
	token = tmp2;
}
