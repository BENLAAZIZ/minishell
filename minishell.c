/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:35:52 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/13 18:34:04 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	set_data(t_env **env, t_box *box)
{
	g_get_status = 0;
	box->i = 0;
	if (*env == NULL)
	{
		*env = malloc(sizeof(t_env));
		(*env)->value = NULL;
		(*env)->variable = NULL;
		(*env)->next = NULL;
	}
	ft_initialis_data(box, *env, 0, 0);
}

void	ft_minishell(t_env **env, t_box *box, struct termios *term, int flag)
{
	while (1)
	{
		set_std(box, 1);
		set_data(env, box);
		flag = 0;
		box->line = readline("minishell$ ");
		if (!box->line || box->line[0] == '\0')
			if (check_empty_line(box, env) == -1)
				continue ;
		add_history(box->line);
		set_std(box, 2);
		if (ft_pars(box, env) == -1)
			continue ;
		if (execute_line(env, box, &flag) == -1)
		{
			(free_data(box), ft_lstclear_token(&box->token));
			free_array_fd(box);
			continue ;
		}
		if (flag == 1)
			box->var.status = 1;
		clean_to_restor(box, term, 1);
	}
	clean_to_restor(box, term, 2);
}

int	main(int argc, char *argv[], char **ev)
{
	t_box			box;
	t_env			*env;
	int				flag;
	struct termios	original_termios;

	get_terminal_attr(&original_termios);
	(void)argc;
	(void)argv;
	flag = 0;
	rl_catch_signals = 0;
	signal(SIGINT, handle_siginit);
	signal(SIGQUIT, handle_siginit);
	env = NULL;
	box.fd_stdin = dup(0);
	box.fd_stdout = dup(1);
	box.var.status = 0;
	ft_env(ev, &env);
	ft_minishell(&env, &box, &original_termios, flag);
	(close(box.fd_stdin), close(box.fd_stdout));
	ft_lstclear_env(&env);
	return (0);
}
