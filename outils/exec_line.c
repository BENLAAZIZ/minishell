/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:06:26 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/07 20:12:15 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	make_one_process(t_env **env, t_box *box)
{
	int	b;

	box->node->flag_r = 0;
	box->var.status = 0;
	if (handle_redirection(&box->node->flag_r,
			box->node->red_node, &box->node->fd_herd) == -1)
	{
		box->var.status = 1;
		return (-1);
	}
	b = built_functions(env, &box->var, box);
	if (b == -1)
	{
		signal(SIGINT, signal_in_child);
		box->pid = fork();
		if (box->pid == 0)
		{
			ft_execute(box->node->command, &box->data, box);
		}
		box->id = box->pid;
		wait_function(box->nbr_node, box);
		signal(SIGINT, handle_siginit);
	}
	return (0);
}

void	in_child_process(t_env **env, t_box *box)
{
	int	b;

	close(box->fd[0]);
	if (box->node->flag_r == 0)
	{
		dup2(box->fd[1], 1);
		close(box->fd[1]);
		if (box->node->next == NULL)
		{
			dup2(box->fd_stdout, 1);
			close(box->fd_stdout);
		}
	}
	b = built_functions(env, &box->var, box);
	if (b == -1)
		ft_execute(box->node->command, &box->data, box);
	exit(box->var.status);
}

int	check_redirection(t_box *box)
{
	int	c;

	c = handle_redirection(&box->node->flag_r,
			box->node->red_node, &box->node->fd_herd);
	if (c == -1)
	{
		box->var.status = 1;
		return (-1);
	}
	return (0);
}

void	make_all_process(t_env **env, t_box *box, int c)
{
	t_node		*tmp;

	box->var.status = 0;
	tmp = box->node;
	while (box->node)
	{
		if (pipe(box->fd) == -1)
			perror("pipe fail :");
		box->node->flag_r = 0;
		c = check_redirection(box);
		signal(SIGINT, signal_in_child);
		if (c != -1)
		{
			box->pid = fork();
			if (box->pid == 0)
				in_child_process(env, box);
			box->id = box->pid;
		}
		else
			box->var.status = 1;
		close(box->fd[1]);
		(dup2(box->fd[0], 0), close(box->fd[0]));
		box->node = box->node->next;
	}
	box->node = tmp;
}

int	execute_line(t_env **env, t_box *box)
{
	if (box->token == NULL || check_syntax(box->token) == 1)
		return (box->var.status = 258, -1);
	(*env)->status = box->var.status;
	if (ft_list_cmd (box->token, &box->node, *env, box) == -1)
		return (ft_lstclear_cmd(&box->node), -1);
	if (signal_hdoc(2) == 1)
		return (ft_lstclear_cmd(&box->node), signal_hdoc(0), -1);
	box->tmp_node = box->node;
	box->nbr_node = size_node(box->node);
	if (box->node->next == NULL)
	{
		if (make_one_process(env, box) == -1)
			return (ft_lstclear_cmd(&box->node), -1);
	}
	else
	{
		make_all_process(env, box, 1);
		wait_function(box->nbr_node, box);
		signal(SIGINT, handle_siginit);
	}
	return (0);
}
