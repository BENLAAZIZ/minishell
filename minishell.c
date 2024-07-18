/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:35:52 by hben-laz          #+#    #+#             */
/*   Updated: 2024/07/18 19:51:12 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	get_cmd_env(t_env *env, t_path *data, char	*tmp, int *i)
{
	tmp = ft_strjoin(env->variable, "=");
	data->cmd_env[*i] = ft_strjoin(tmp, env->value);
	(*i)++;
}

void	ft_initialis_data(t_path *data, t_env *env, int size, int i)
{
	t_env	*poin;
	t_env	*tp;
	char	*tmp;
	char	*str;

	tp = env;
	poin = point_node(env, "PATH");
	if (!poin)
		return ;
	str = poin->value;
	data->cmd_env = NULL;
	data->path = ft_splith(str, ':');
	size = size_env(env);
	data->cmd_env = (char **)malloc(sizeof(char *) * (size + 1));
	while (env)
	{
		tmp = NULL;
		if (env->value)
			get_cmd_env(env, data, tmp, &i);
		free(tmp);
		env = env->next;
	}
	data->cmd_env[i] = NULL;
	env = tp;
}


//***************************************

//*****************************************



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
//****************************************

int	in_child_process(t_env **env, int c, t_variable *varr)
{
	int b;
			if (c == -1 || c == 0)
			{
				if (c == -1)
				{
					varr->node = varr->node->next;
					return (-1);;
				}
			}
			if (varr->node->flag_r == 0)
			{
				close(varr->fd[0]);
				dup2(varr->fd[1], 1);
				close(varr->fd[1]);
				if (varr->node->next == NULL)
					dup2(varr->fd_stdout, 1);
			}
			b = built_functions(env, &varr->var, varr->node->command);
			if (b == -1)
				ft_execute(varr->node->command, &varr->data, &varr->var);
			return (0);
}

void	make_all_process(t_env **env, t_variable *varr)
{
	int c;
	// int b;
	int pid;

	while (varr->node)
	{
		if (pipe(varr->fd) == -1)
			perror("pipe fail :");
		varr->node->flag_r = 0;
		c = handle_redirection(&varr->node->flag_r, varr->node->red_node);
		pid = fork();
		if (pid == 0)
		{
			if (in_child_process(env, c, varr) == -1)
				continue ;
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



//*****************************************


void	ft_minishell(t_env **env, t_variable *varr)
{
	while (1)
	{
		// varr->var.status = 0;
		(dup2(varr->fd_stdin, 0), dup2(varr->fd_stdout, 1));
		varr->line = readline("minishell$ ");
		if (!varr->line || varr->line[0] == '\0')
			continue ; 
		add_history(varr->line);// 1
		rl_redisplay(); // 1
		if (check_quotes(varr->line) == 1) // 1
			continue ; // 1
		ft_initialis_data(&varr->data, *env, 0, 0); // 2
		varr->token = ft_list_tokn(varr->line, varr->token, *env);
		word_expand(varr->token, *env); // 2
		remove_quotes(varr->token); // 2
		if (varr->token == NULL || check_syntax(varr->token) == 1)
		{
			ft_lstclear_token(&varr->token);
			free(varr->line);
			continue ;
		}
		ft_list_cmd (varr->token, &varr->node); // 2
		varr->tmp_node = varr->node; // for save head node
		ft_lstclear_token(&varr->token);	// 2

		varr->nbr_node = size_node(varr->node);
		// exec -----------------
		if (varr->node->next == NULL)
		{
			if (make_one_process(env, varr) == -1 )
				continue ;
		}
		else 
		{
			make_all_process(env, varr);
			wait_function(varr->nbr_node);
		}
		// -----------------
		if (varr->data.path)
			free_t_split(varr->data.path);
		if (varr->data.cmd_env)
			free_t_split(varr->data.cmd_env);
		free(varr->line);
		varr->node = varr->tmp_node;
		ft_lstclear_red(&varr->node->red_node);
		ft_lstclear_cmd(&varr->	node);
	}
}


int	main(int argc, char *argv[], char **ev)
{
	t_variable	varr;
	t_env		*env;
	

	// **********************************
	varr.node = NULL;
	varr.token = NULL;
	varr.line = NULL;
	varr.fd_stdin = dup(0);
	varr.fd_stdout = dup(1);
	varr.var.status = 0;
	// ***********************************
	env = NULL;
	(void)argc;
	(void)argv;
	ft_env(ev, &env);
	ft_minishell(&env, &varr);
	return (0);
}
