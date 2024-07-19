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
		// free(tmp->val_noquotes);
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
		// free(tmp->val_noquotes);
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
		free(tmp->command);
		// free(tmp->val_noquotes);
		free(tmp);
	}
	*list = NULL;
}
