/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:35:52 by hben-laz          #+#    #+#             */
/*   Updated: 2024/07/28 18:02:08 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstclear_env(t_env **env)
{
	t_env	*tmp;

	if (env == NULL || (*env) == NULL)
	{
		pause();
		return ;
	}
	tmp = (*env);
	while ((*env) != NULL)
	{
		tmp = (*env);
		(*env) = (*env)->next;
		free(tmp->variable);
		free(tmp->value);
		tmp->variable = NULL;
		tmp->value = NULL;
		free(tmp);
	}
	*env = NULL;
}

void	get_cmd_env(t_env *env, t_path *data, char	*tmp, int *i)
{
	tmp = ft_strjoin(env->variable, "=");
	data->cmd_env[*i] = ft_strjoin(tmp, env->value);
	(*i)++;
}

void	ft_initialis_data(t_variable *varr, t_env *env, int size, int i)
{
	t_env	*poin;
	t_env	*tp;
	char	*tmp;
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
		tmp = NULL;
		if (env->value)
			get_cmd_env(env, &varr->data, tmp, &i);
		free(tmp);
		env = env->next;
	}
	varr->data.cmd_env[i] = NULL;
	env = tp;
}


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
		return (-1) ;
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
	int b;

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
	int c;

	c = handle_redirection(&varr->node->flag_r,
		varr->node->red_node, &varr->node->fd_herd);
	if (c == -1)
	{
		varr->var.status = 1;
		varr->node = varr->node->next;
		return (-1);;
	}
	return (0);
}

void	make_all_process(t_env **env, t_variable *varr)
{
	int pid;

	varr->var.status = 0;
	while (varr->node)
	{
		if (pipe(varr->fd) == -1)
			perror("pipe fail :");
		varr->node->flag_r = 0;
		pid = fork();
		if (pid == 0)
		{
			if (check_redirection(varr) == -1)
				exit(varr->var.status);
			in_child_process(env, varr);
		}
		varr->id = pid;
		if (varr->node->flag_r == 0)
		{
			close(varr->fd[1]);
			dup2(varr->fd[0], 0);
			close(varr->fd[0]);	
		}
		varr->node = varr->node->next;
	}
}

void	free_data(t_variable *varr)
{
	if (varr->data.path)
		free_t_split(varr->data.path);
	if (varr->data.cmd_env)
		free_t_split(varr->data.cmd_env);
	if (varr->line)
		free(varr->line);
	varr->node = varr->tmp_node;
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
		if (varr->node->next == NULL)
		{
			if (make_one_process(env, varr) == -1 )
				return (-1);
		}
		else 
		{
			make_all_process(env, varr);
			wait_function(varr->nbr_node, varr);
		}
		free_data(varr);
		return (0);
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
			printf("exit\n");
			ft_lstclear_token(&varr->token);
			ft_lstclear_cmd(&varr->node);
			ft_lstclear_env(env);
			rl_clear_history();
			exit(varr->var.status);
		}
		if (varr->line[0] == '\0')
			continue ; 
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
			continue ; 
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
		ft_lstclear_token(&varr->token);
		ft_lstclear_cmd(&varr->node);
	}
	ft_lstclear_token(&varr->token);
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
