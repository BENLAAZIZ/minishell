/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:06:26 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/01 17:28:17 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_one_process(t_env **env, t_variable *varr)
{
	int	b;
	int	pid;

	varr->node->flag_r = 0;
	varr->var.status = 0;
	if (handle_redirection(&varr->node->flag_r,
			varr->node->red_node, &varr->node->fd_herd) == -1)
	{
		varr->var.status = 1;
		return (-1);
	}
	b = built_functions(env, &varr->var, varr);
	if (b == -1)
	{
		pid = fork();
		if (pid == 0)
			ft_execute(varr->node->command, &varr->data, varr);
		varr->id = pid;
		wait_function(varr->nbr_node, varr);
	}
	return (0);
}

void	in_child_process(t_env **env, t_variable *varr)
{
	int	b;

	close(varr->fd[0]);
	if (varr->node->flag_r == 0)
	{
		dup2(varr->fd[1], 1);
		close(varr->fd[1]);
		if (varr->node->next == NULL)
		{
			dup2(varr->fd_stdout, 1);
			close(varr->fd_stdout);
		}
	}
	b = built_functions(env, &varr->var, varr);
	if (b == -1)
		ft_execute(varr->node->command, &varr->data, varr);
	exit(varr->var.status);
}

int	check_redirection(t_variable *varr)
{
	int	c;

	c = handle_redirection(&varr->node->flag_r,
			varr->node->red_node, &varr->node->fd_herd);
	if (c == -1)
	{
		varr->var.status = 1;
		return (-1);
	}
	return (0);
}

void	make_all_process(t_env **env, t_variable *varr, int c)
{
	t_cmd_node	*tmp;
	int			pid;

	varr->var.status = 0;
	tmp = varr->node;
	while (varr->node)
	{
		if (pipe(varr->fd) == -1)
			perror("pipe fail :");
		varr->node->flag_r = 0;
		c = check_redirection(varr);
		if (c != -1)
		{
			pid = fork();
			if (pid == 0)
				in_child_process(env, varr);
			varr->id = pid;
		}
		else
			varr->var.status = 1;
		close(varr->fd[1]);
		(dup2(varr->fd[0], 0), close(varr->fd[0]));
		varr->node = varr->node->next;
	}
	varr->node = tmp;
}

int	execute_line(t_env **env, t_variable *varr)
{
	if (varr->token == NULL || check_syntax(varr->token) == 1)
	{
		varr->var.status = 258;
		ft_lstclear_token(&varr->token);
		return (-1);
	}
	ft_list_cmd (varr->token, &varr->node, *env);
	varr->tmp_node = varr->node;
	varr->nbr_node = size_node(varr->node);
	add_history(varr->line);
	if (varr->node->next == NULL)
	{
		if (make_one_process(env, varr) == -1)
			return (-1);
	}
	else
	{
		make_all_process(env, varr, 1);
		wait_function(varr->nbr_node, varr);
	}
	return (0);
}
