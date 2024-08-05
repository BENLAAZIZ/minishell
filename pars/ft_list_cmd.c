/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:07:47 by aaaraba           #+#    #+#             */
/*   Updated: 2024/08/05 10:29:01 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	copy_in_cmds(t_word **token, char **cmds, int *j, int x)
{
	if ((*token)->is_expand == 1)
	{
		if ((*token)->val_noquotes && (*token)->val_noquotes[0] != '\0')
		{
			(*token)->split_value = ft_split((*token)->val_noquotes, ' ', 0);
			if ((*token)->split_value == NULL)
				return ;
			while ((*token)->split_value[x] != NULL)
			{
				cmds[*j] = (*token)->split_value[x];
				x++;
				(*j)++;
			}
		}
	}
	else
		cmds[(*j)++] = (*token)->val_noquotes;
	*token = (*token)->next;
}

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
			copy_in_cmds(token, cmds, &j, x);
		cmds[j] = NULL;
	}
	return (cmds);
}

void	ft_list_cmd(t_word	*token, t_node **cmd, t_env *env)
{
	char		**cmds;
	t_node		*commands;
	t_word		*tmp;
	t_word		*tmp2;
	t_node		*node;

	cmds = NULL;
	commands = NULL;
	tmp2 = token;
	tmp = token;
	while (token != NULL)
	{
		cmds = add_cmds_files(&token);
		commands = ft_addnode_cmds(cmds);
		node = ft_lstaddback_cmd(cmd, commands);
		list_file(tmp, &(commands->red_node), node, env);
		if (token && token->next != NULL)
		{
			token = token->next;
			tmp = token;
		}
	}
	token = tmp2;
}
