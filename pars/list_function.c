#include "minishell.h"

void	ft_lstclear_token(t_word **list)
{
	t_word	*tmp;

	if (list == NULL || (*list) == NULL)
		return ;
	tmp = (*list);
	while ((*list) != NULL)
	{
		tmp = (*list);
		(*list) = (*list)->next;
		free(tmp->value);
		free(tmp->old_word);
		free(tmp->val_noquotes);
		free(tmp->line);
		free_t_split(tmp->split_value);
		tmp->val_noquotes = NULL;
		tmp->value = NULL;
		free(tmp);
	}
	*list = NULL;
}

void	ft_lstclear_red(t_red_node **list)
{
	t_red_node	*tmp;

	if (list == NULL || (*list) == NULL)
		return ;
	tmp = (*list);
	while ((*list) != NULL)
	{
		tmp = (*list);
		(*list) = (*list)->next;
		free(tmp->red);
		free(tmp->file);
		if (tmp->exp)
			free(tmp->exp);
		free(tmp);
	}
	*list = NULL;
}
void	ft_lstclear_cmd(t_cmd_node **list)
{
	t_cmd_node	*tmp;

	if (list == NULL || (*list) == NULL)
		return ;
	tmp = (*list);
	while ((*list) != NULL)
	{
		tmp = (*list);
		(*list) = (*list)->next;
		ft_lstclear_red(&tmp->red_node);
		tmp->red_node = NULL;
		free(tmp->command);
		tmp->command = NULL;
		free(tmp);
	}
	*list = NULL;
}
