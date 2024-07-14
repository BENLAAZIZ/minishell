/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:35:52 by hben-laz          #+#    #+#             */
/*   Updated: 2024/07/14 19:15:47 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_env(t_env *a)
{
	while (a)
	{
		if (a->value != NULL)
			printf("%s=%s\n", a->variable, a->value);
		a = a->next;
	}
}
//============== start 

// =============== end

void	ft_initialis_data(t_path *data, t_env *env, int size, int i)
{
	t_env	*poin;
	char	*tmp;
	t_env	*tp;
	char *str;
	
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
		{	
			tmp = ft_strjoin(env->variable, "=");
			data->cmd_env[i] = ft_strjoin(tmp, env->value);
			i++;
		}
		free(tmp);
		env = env->next;
	}
	data->cmd_env[i] = NULL;
	env = tp;
}


int built_functions(t_env **env, t_var *var, char **cmd)
{
	if (!env || !env[0])
	{
		printf("env failed\n");
		// while (1);
		
	}
		if (!cmd || !cmd[0])
	{
		printf("cmd failed\n");
		// while (1);
		
	}
		if (ft_strncmp(cmd[0], "env", 4) == 0)
		{
			if (cmd[1])
			{
				printf("env: %s: No such file or directory\n", cmd[1]);
				var->status = 1;
			}
			else 
				display_env(*env);
		}
		else if (ft_strncmp(cmd[0], "echo", 5) == 0)
			echo(cmd);
		else if (ft_strncmp(cmd[0], "cd", 3) == 0)
			var->status = cd(cmd, env);
		else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
			var->status = pwd();
		else if (ft_strncmp(cmd[0], "export", 7) == 0)
			var->status = export(env , cmd);
		else if (ft_strncmp(cmd[0], "unset", 6) == 0)
			unset(env, cmd, var);
		else if (ft_strncmp(cmd[0], "exit", 6) == 0)
			ft_exit(cmd, var);
		else
			return (-1);
		return (0);
}



void	handle_rederection(t_red_node *red_node)
{
	int		fd;
	int		fd_in;
	int		fd_out;

	fd_in = -1;
	fd_out = -1;
	fd = -1;
	if (!red_node)
		return ;
	while (red_node)
	{
		if (ft_strncmp(red_node->red, "<<", 2) == 0 || ft_strncmp(red_node->red, "<", 1) == 0)
		{
			if (ft_strncmp(red_node->red, "<<", 3) == 0)
			{
				dup2(*(red_node)->fd_herdoc, 1);
				close(*(red_node)->fd_herdoc);
			}
			else
			{
					fd_in = open(red_node->file, O_RDONLY, 0644);
					if (fd_in < 0)
					{
						if (red_node->expand == 1)
							printf("minishell: %s: ambiguous redirect\n", red_node->exp);
						else
							printf("minishell: %s: No such file or directory\n", red_node->file);
						exit(1);
					}
					dup2(fd_in, 1);
					close(fd_in);
			}
		}
		else if (ft_strncmp(red_node->red, ">>", 3) == 0 || ft_strncmp(red_node->red, ">", 2) == 0)
		{
			if (ft_strncmp(red_node->red, ">>", 3) == 0)
					fd_out = open(red_node->red, O_CREAT, O_RDWR, O_APPEND, 0644);
			else
					fd_out = open(red_node->red, O_CREAT, O_RDWR, O_TRUNC, 0644);
			if (fd_out < 0)
			{
				if (red_node->expand == 1)
					printf("minishell: %s: ambiguous redirect\n", red_node->exp);
				exit(1);
			}
			dup2(fd_out, 0);
			close(fd_out);
		}
		red_node = red_node->next;
	}
}

//***************************************


// t_node	*get_pars(void)
// {
// 	t_node *node;
// 	node = NULL;
// 	node = malloc(sizeof(t_node));
// 	node->red_node  = get_red_nod();
// 	// display_red(node->red_node);
// 	char *cmd = "ls -la";
// 	// int i = -1;
	
// 	// while(++i < 3)
// 	// 	ft_lstadd_back_node(&node, ft_lstnew_node(ft_splith(cmd[i], 32)));
// 	node->cmd_node = ft_splith(cmd, 32);
// 	if (!node->cmd_node)
// 		return NULL;
// 	display_node(node);
// 	return (node);
// }

// #include <string.h>

// void make_process(t_cmd_node *node, int *fd_out)
// {
// 	int pid;
// 	int fd[2];

// 	pipe(fd);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		close(fd[0]);
// 		if (!strcmp(node->command[0], "wc"))
// 		{
// 			printf("tetse\n");
// 			dup2(*fd_out, 1);
// 			close(*fd_out);
// 		}
// 		else
// 		{
// 			dup2(fd[1], 1);
// 			close(fd[1]);
// 		}
// 		execve(node->command[0], node->command, NULL);	
// 		exit(1);
// 	}
// 	close(fd[1]);
// 	dup2(fd[0], 0);
// 	close(fd[0]);
// 	printf("parent\n");
// }

//*****************************************

void	ft_minishell(t_env **env)
{
	t_word		*token;
	t_red_node	*files;
	t_cmd_node	*node;
	t_path	data;
	t_var	var;
	char	*line;
	int		size;
	// int		fdd[2];
	// int		*fd;
	int		pid;
	int		i;
	int b;
	node = NULL;
	files = NULL;
	token = NULL;
	line = NULL;
	while (1)
	{
		i = 0;
		var.status = 0;
		line = readline("minishell$ ");
		if (!line || line[0] == '\0')
			continue ; 
		add_history(line);
		rl_redisplay();
		if (check_quotes(line) == 1)
			continue ;
		ft_initialis_data(&data, *env, 0, 0);
		// size = size_pipe_node(pipe_node);
		//=======
		token = ft_list_tokn(line, token, *env);
		word_expand(token, *env);
		remove_quotes(token);
		if (token == NULL || check_syntax(token) == 1)
		{
			ft_lstclear_token(&token);
			free(line);
			continue ;
		}
		ft_list_cmd (token, &node);
		ft_lstclear_token(&token);	
		//==============

		// printf("{env = %s}\n", (*env)->variable);
		// desplay_node(node);
		// pause();
			
		// node = get_pars();
		size = 1; // hadi ghi bach njarab node whda
		if (size == 1)
		{
			handle_rederection(node->red_node);
			b = built_functions(env, &var, node->command);
			// printf("b %d\n", b);
			if (b == -1)
			{
				pid = fork();
				if (pid == 0)
					ft_exuctute(node->command, &data, &var);
				// wait(NULL);
				//===========
				int i = -1;
				i = -1;
				while(++i < 3)
					wait(NULL);
			}
		}
		if (data.path)
			free_t_split(data.path);
		if (data.cmd_env)
			free_t_split(data.cmd_env);
		free(line);
		ft_lstclear_red(&node->red_node);
		ft_lstclear_cmd(&node);
	}
}


int	main(int argc, char *argv[], char **ev)
{
	t_env	*env;
	char	**cmd;

	(void)argc;
	(void)argv;
	cmd = NULL;
	ft_env(ev, &env);
	ft_minishell(&env);
	return (0);
}
