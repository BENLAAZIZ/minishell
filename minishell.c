/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:35:52 by hben-laz          #+#    #+#             */
/*   Updated: 2024/07/19 22:07:46 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (handle_redirection(&varr->node->flag_r, varr->node->red_node) == -1)
		return (-1) ;
	b = built_functions(env, &varr->var, varr->node->command);
	if (b == -1)
	{
		pid = fork();
		if (pid == 0)
			ft_execute(varr->node->command, &varr->data, &varr->var);
		wait(NULL);
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
	b = built_functions(env, &varr->var, varr->node->command);
	if (b == -1)
		ft_execute(varr->node->command, &varr->data, &varr->var);
	exit(0);
}

int	check_redirection(t_variable *varr)
{
	int c;

	c = handle_redirection(&varr->node->flag_r, varr->node->red_node);
	if (c == -1)
	{
		varr->node = varr->node->next;
		return (-1);;
	}
	return (0);
}

void	make_all_process(t_env **env, t_variable *varr)
{
	int pid;

	while (varr->node)
	{
		if (pipe(varr->fd) == -1)
			perror("pipe fail :");
		varr->node->flag_r = 0;
		pid = fork();
		if (pid == 0)
		{
			if (check_redirection(varr) == -1)
				exit(1);
			in_child_process(env, varr);
		}
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
	free(varr->line);
	varr->node = varr->tmp_node;
	ft_lstclear_cmd(&varr->	node);
}


int	execute_line(t_env **env, t_variable *varr)
{
	if (varr->token == NULL || check_syntax(varr->token) == 1)
		{
			ft_lstclear_token(&varr->token);
			free(varr->line);
			return (-1);
		}
		ft_list_cmd (varr->token, &varr->node);
		varr->tmp_node = varr->node;
		ft_lstclear_token(&varr->token);
		varr->nbr_node = size_node(varr->node);
		if (varr->node->next == NULL)
		{
			if (make_one_process(env, varr) == -1 )
				return (-1);
		}
		else 
		{
			make_all_process(env, varr);
			wait_function(varr->nbr_node);
		}
		free_data(varr);
		return (0);
}

void	ft_minishell(t_env **env, t_variable *varr)
{
	while (1)
	{
		(dup2(varr->fd_stdin, 0), dup2(varr->fd_stdout, 1));
		varr->line = readline("minishell$ ");
		if (!varr->line || varr->line[0] == '\0')
			continue ; 
		add_history(varr->line);
		rl_redisplay(); 
		if (check_quotes(varr->line) == 1)
		{
			free_data(varr);
			continue ;
		}
		ft_initialis_data(varr, *env, 0, 0);
		varr->token = ft_list_tokn(varr->line, varr->token, *env);
		word_expand(varr->token, *env);
		remove_quotes(varr->token);

		if (execute_line(env, varr) == -1)
		{
			free_data(varr);
			continue ;
		}
	}
}

// void	ft_lstclear_env(t_env **env)
// {
// 	t_env	*tmp;

// 	if (env == NULL || (*env) == NULL)
// 	{
// 		pause();
// 		return ;
// 	}
// 	tmp = (*env);
// 	while ((*env) != NULL)
// 	{
// 		tmp = (*env);
// 		(*env) = (*env)->next;
// 		free(tmp->variable);
// 		free(tmp->value);
// 		free(tmp);
// 	}
// 	*env = NULL;
// }

// void	v()
// {
// 	system("leaks minishell");
// }
int	main(int argc, char *argv[], char **ev)
{
	t_variable	varr;
	t_env		*env;
	// atexit(v);
	(void)argc;
	(void)argv;
	varr.node = NULL;
	varr.token = NULL;
	varr.line = NULL;
	env = NULL;
	varr.fd_stdin = dup(0);
	varr.fd_stdout = dup(1);
	varr.var.status = 0;
	ft_env(ev, &env);
	ft_minishell(&env, &varr);
	// ft_lstclear_env(&env);
	return (0);
}
