/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaaraba <aaaraba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:35:52 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/04 16:11:41 by aaaraba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_initialis_data(t_variable *varr, t_env *env, int size, int i)
{
	t_env	*poin;
	t_env	*tp;

	varr->data.path = NULL;
	varr->data.cmd_env = NULL;
	varr->node = NULL;
	varr->token = NULL;
	varr->line = NULL;
	tp = env;
	poin = point_node(env, "PATH");
	if (!poin)
		return ;
	varr->data.path = ft_splith(poin->value, ':');
	size = size_env(env);
	varr->data.cmd_env = (char **)malloc(sizeof(char *) * (size + 1));
	while (env)
	{
		if (env->value)
			get_cmd_env(env, &varr->data, &i);
		env = env->next;
	}
	varr->data.cmd_env[i] = NULL;
	env = tp;
}

int	ft_pars(t_variable *varr, t_env **env)
{
	if (check_quotes(varr->line) == 1)
	{
		free_data(varr);
		return (-1);
	}
	varr->token = ft_list_tokn(varr->line, varr->token, *env);
	if (!varr->token)
	{
		free_data(varr);
		return (-1);
	}
	word_expand(varr->token, *env, varr);
	if (remove_quotes(varr->token, 0, 0, 0) == 0)
	{
		varr->var.status = 1;
		ft_lstclear_token(&varr->token);
		free(varr->line);
		return (-1);
	}
	return (0);
}

int	check_empty_line(t_variable *varr, t_env **env)
{
	if (!varr->line)
	{
		write(1, "exit\n", 5);
		free_data(varr);
		ft_lstclear_env(env);
		rl_clear_history();
		exit(varr->var.status);
	}
	if (varr->line[0] == '\0')
	{
		free_data(varr);
		return (-1);
	}
	rl_redisplay();
	return (0);
}

void	ft_minishell(t_env **env, t_variable *varr, struct termios *term)
{
	while (1)
	{
		ft_initialis_data(varr, *env, 0, 0);
		(dup2(varr->fd_stdin, 0), dup2(varr->fd_stdout, 1));
		varr->line = readline("minishell$ ");
		if (!varr->line || varr->line[0] == '\0')
			if (check_empty_line(varr, env) == -1)
				continue ;
		add_history(varr->line);
		if (ft_pars(varr, env) == -1)
			continue ;
		if (execute_line(env, varr) == -1)
			continue ;
		free_data(varr);
		ft_lstclear_cmd(&varr->node);
		ft_lstclear_token(&varr->token);
		restore_terminal_attributes(term);
	}
	ft_lstclear_token(&varr->token);
	ft_lstclear_env(env);
	free(varr->line);
}

int	main(int argc, char *argv[], char **ev)
{
	t_variable		varr;
	t_env			*env;
	struct termios	original_termios;

	get_terminal_attr(&original_termios);
	(void)argc;
	(void)argv;
	rl_catch_signals = 0;
	signal(SIGINT, handle_siginit);
	signal(SIGQUIT, handle_siginit);
	env = NULL;
	varr.fd_stdin = dup(0);
	varr.fd_stdout = dup(1);
	varr.var.status = 0;
	ft_env(ev, &env);
	ft_minishell(&env, &varr, &original_termios);
	return (0);
}
