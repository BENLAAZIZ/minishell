/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:35:52 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/05 14:45:14 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_initialis_data(t_box *box, t_env *env, int size, int i)
{
	t_env	*poin;
	t_env	*tp;

	box->data.path = NULL;
	box->data.cmd_env = NULL;
	box->node = NULL;
	box->token = NULL;
	box->line = NULL;
	tp = env;
	poin = point_node(env, "PATH");
	if (!poin)
		return ;
	box->data.path = ft_splith(poin->value, ':');
	size = size_env(env);
	box->data.cmd_env = (char **)malloc(sizeof(char *) * (size + 1));
	while (env)
	{
		if (env->value)
			get_cmd_env(env, &box->data, &i);
		env = env->next;
	}
	box->data.cmd_env[i] = NULL;
	env = tp;
}

int	ft_pars(t_box *box, t_env **env)
{
	if (check_quotes(box->line) == 1)
	{
		free_data(box);
		box->var.status = 258;
		return (-1);
	}
	box->token = ft_list_tokn(box->line, box->token, *env);
	if (!box->token)
	{
		free_data(box);
		return (-1);
	}
	word_expand(box->token, *env, box);
	if (remove_quotes(box->token, 0, 0, 0) == 0)
	{
		box->var.status = 1;
		ft_lstclear_token(&box->token);
		free(box->line);
		return (-1);
	}
	return (0);
}

int	check_empty_line(t_box *box, t_env **env)
{
	if (!box->line)
	{
		write(1, "exit\n", 5);
		free_data(box);
		ft_lstclear_env(env);
		rl_clear_history();
		exit(box->var.status);
	}
	if (box->line[0] == '\0')
	{
		free_data(box);
		return (-1);
	}
	rl_redisplay();
	return (0);
}

void	ft_minishell(t_env **env, t_box *box, struct termios *term)
{
	while (1)
	{
		ft_initialis_data(box, *env, 0, 0);
		(dup2(box->fd_stdin, 0), dup2(box->fd_stdout, 1));
		box->line = readline("minishell$ ");
		if (!box->line || box->line[0] == '\0')
			if (check_empty_line(box, env) == -1)
				continue ;
		add_history(box->line);
		if (ft_pars(box, env) == -1)
			continue ;
		if (execute_line(env, box) == -1)
		{
			free_data(box);
			ft_lstclear_token(&box->token);
			continue ;
		}
		free_data(box);
		ft_lstclear_cmd(&box->node);
		ft_lstclear_token(&box->token);
		restore_terminal_attributes(term);
	}
	ft_lstclear_token(&box->token);
	ft_lstclear_env(env);
	free(box->line);
}

int	main(int argc, char *argv[], char **ev)
{
	t_box			box;
	t_env			*env;
	struct termios	original_termios;

	get_terminal_attr(&original_termios);
	(void)argc;
	(void)argv;
	rl_catch_signals = 0;
	signal(SIGINT, handle_siginit);
	signal(SIGQUIT, handle_siginit);
	env = NULL;
	box.fd_stdin = dup(0);
	box.fd_stdout = dup(1);
	box.var.status = 0;
	ft_env(ev, &env);
	ft_minishell(&env, &box, &original_termios);
	return (0);
}
