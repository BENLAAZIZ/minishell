/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:35:52 by hben-laz          #+#    #+#             */
/*   Updated: 2024/07/31 18:55:50 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_cmd_env(t_env *env, t_path *data, int *i)
{
	char	*tmp;

	tmp = ft_strjoin(env->variable, "=");
	data->cmd_env[*i] = ft_strjoin(tmp, env->value);
	free(tmp);
	(*i)++;
}

void	ft_initialis_data(t_variable *varr, t_env *env, int size, int i)
{
	t_env	*poin;
	t_env	*tp;
	char	*str;
	
	varr->data.path = NULL;
	varr->data.cmd_env = NULL;
	varr->node = NULL;
	varr->token = NULL;
	tp = env;
	poin = point_node(env, "PATH");
	if (!poin)
		return ;
	str = poin->value;
	varr->data.path = ft_splith(str, ':');
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

void	display_red(t_red_node *red)
{
	if (!red)
		return;
		while (red)
		{
			printf("\n [%s %s] ", red->red, red->file);
			red = red->next;
		}
		
}

void	display_node(t_cmd_node *node)
{
	if (!node)
	{
		printf("khaaaawya mafiha walo\n");
		return;
	}
		while (node)
		{
			printf("\n-----------------------------------\n");
			display_red(node->red_node);
			printf("\n {%s} ", node->command[0]);
			printf("\n-----------------------------------\n");
			node = node->next;
		}
		
}


void	ft_minishell(t_env **env, t_variable *varr)
{
	while (1)
	{
		ft_initialis_data(varr, *env, 0, 0);
		(dup2(varr->fd_stdin, 0), dup2(varr->fd_stdout, 1));
		varr->line = readline("minishell$ ");
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
			rl_clear_history();
			continue ; 
		}
		add_history(varr->line);
		rl_redisplay(); 
		if (check_quotes(varr->line) == 1)
		{
			free_data(varr);
			continue ;
		}
		varr->token = ft_list_tokn(varr->line, varr->token, *env);
		word_expand(varr->token, *env, varr);
		if (varr->token->value[0] == '\0')
		{
			free_data(varr);
			continue ; 
		}
		if (remove_quotes(varr->token, 0, 0, 0) == 0)
		{
			varr->var.status = 1;
			ft_lstclear_token(&varr->token);
			free(varr->line);
			continue ;
		}
		if (execute_line(env, varr) == -1)
		{
			free_data(varr);
			continue ;
		}
		ft_lstclear_cmd(&varr->node);
		ft_lstclear_token(&varr->token);
		// close(varr->fd_stdout);
		// close(varr->fd_stdin);
	} 
	ft_lstclear_token(&varr->token);
	ft_lstclear_env(env);
	ft_lstclear_cmd(&varr->node);
	rl_clear_history();
	free(varr->line);
	close(varr->fd_stdout);
	close(varr->fd_stdin);
}



void	v()
{
	system("leaks minishell");
}

void handle_siginit(int sig)
{
	
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
		return ;
}

int	main(int argc, char *argv[], char **ev)
{
	t_variable	varr;
	t_env		*env;
	// atexit(v);
	(void)argc;
	(void)argv;
	rl_catch_signals = 0;
	signal(SIGINT, handle_siginit);
	signal(SIGQUIT, handle_siginit);
	varr.node = NULL;
	varr.token = NULL;
	varr.line = NULL;
	env = NULL;
	varr.fd_stdin = dup(0);
	varr.fd_stdout = dup(1);
	varr.var.status = 0;
	ft_env(ev, &env);  
	ft_minishell(&env, &varr);
	ft_lstclear_env(&env);
	return (0);
}
