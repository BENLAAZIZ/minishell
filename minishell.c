/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:35:52 by hben-laz          #+#    #+#             */
/*   Updated: 2024/07/16 12:52:55 by hben-laz         ###   ########.fr       */
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



int	handle_redirection(t_cmd_node *node, t_red_node *red_node)
{
	int		fd;
	int		fd_in;
	int		fd_out;

	fd_in = -1;
	fd_out = -1;
	fd = -1;
	if (!red_node)
		return 0;
	while (red_node)
	{
		if (ft_strncmp(red_node->red, "<<", 2) == 0 || ft_strncmp(red_node->red, "<", 2) == 0)
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
						// if (red_node->expand == 1)
						// 	printf("minishell: %s: ambiguous redirect\n", red_node->exp);
						// else
							printf("minishell: %s: No such file or directory \n", red_node->file);
						return (1);
					}
					node->flag_r = 0;
					dup2(fd_in, 0);
					close(fd_in);
					// printf("\n======  if ********   ======\n");
			}
		}
		else if (ft_strncmp(red_node->red, ">>", 3) == 0 || ft_strncmp(red_node->red, ">", 2) == 0)
		{
			if (ft_strncmp(red_node->red, ">>", 3) == 0)
			{
					node->flag_r = 1;
					fd_out = open(red_node->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
			}
			else
			{
					node->flag_r = 1;
					fd_out = open(red_node->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			}
			if (fd_out < 0)
			{
				// if (red_node->expand == 1)
					// printf("minishell: %s: ambiguous redirect\n", red_node->exp);
				return (1);
			}
			dup2(fd_out, 1);
			close(fd_out);
		}
		red_node = red_node->next;
	}
	return (0);
}

//***************************************


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
	t_cmd_node	*tmp_node;
	t_path	data;
	t_var	var;
	char	*line;
	// int		size;
	int		fd[2];
	// int		*fd;
	int		pid;
	int		i;
	int b;
	node = NULL;
	files = NULL;
	token = NULL;
	line = NULL;
	int fd_stdin = dup(0);
	int fd_stdout = dup(1);
	while (1)
	{
		i = 0;
		var.status = 0;
		dup2(fd_stdin, 0);
		dup2(fd_stdout, 1);
		line = readline("minishell$ ");
		if (!line || line[0] == '\0')
			continue ; 
		add_history(line);
		rl_redisplay();
		if (check_quotes(line) == 1)
			continue ;
		// ft_env(ev, env);
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
		tmp_node = node;
		ft_lstclear_token(&token);	
		//==============
		// desplay_node(&node);
		if (node->next == NULL)
		{
			if (handle_redirection(node, node->red_node) == 1)
				continue ;
			b = built_functions(env, &var, node->command);
			if (b == -1)
			{
				pid = fork();
				if (pid == 0)
					ft_execute(node->command, &data, &var);
				wait(NULL);
			}
		}
		else
		{
			while (node)
			{
				if (pipe(fd) == -1)
					perror("pipe fail :");
				node->flag_r = 0;
				pid = fork();
				if (pid == 0)
				{
				// printf("\n====== her seg======\n");
					if (handle_redirection(node, node->red_node) == 1)
					{
						node = node->next;
						continue ;
					}
					b = built_functions(env, &var, node->command);
					// printf("\n node->flag_r = %d\n", node->flag_r);
					if (node->flag_r == 0)
					{
						close(fd[0]);
						dup2(fd[1], 1);
						close(fd[1]);
					}
					if (b == -1)
						ft_execute(node->command, &data, &var);
				}
				if (node->flag_r == 0)
				{
					close(fd[1]);
					dup2(fd[0], 0);
					close(fd[0]);	
				}

				node = node->next;
			}

			wait(NULL);
			wait(NULL);
			
		}
		if (data.path)
			free_t_split(data.path);
		if (data.cmd_env)
			free_t_split(data.cmd_env);
		free(line);
		node = tmp_node;
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
