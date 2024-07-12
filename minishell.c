/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:35:52 by hben-laz          #+#    #+#             */
/*   Updated: 2024/07/12 22:07:50 by hben-laz         ###   ########.fr       */
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

// void	display_red(t_red *a)
// {
// 	while (a)
// 	{
// 			printf("%s %s index = %d\n", a->type, a->red, a->index);
// 		a = a->next;
// 	}
// }

void	display_node(t_node *a)
{
	(void)(a);
	printf("\n hamza \n");
			// printf("%s %s index = %d || %s %s \n", a->red_node->type, a->red_node->red, a->red_node->index, a->cmd_node[0], a->cmd_node[1]);
}

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

// void	handle_pipe(command, env)
// {
	
// }

// void	here_doc(char *limiter, int *fd_in, int fd, int p)
// {
// 	char	*line;

// 	*fd_in = open("herd.txt", O_RDWR | O_CREAT | O_APPEND, 0777);
// 	fd = open("herd.txt", O_RDWR | O_CREAT | O_APPEND, 0777);
// 	if (*fd_in == -1 || fd == -1)
// 		return (ft_error("open fail : \n", "fail", 0, -1));
// 	unlink("herd.txt");
// 	while (1)
// 	{
// 		write(1, "> ", 2);
// 		line = get_next_line(0);
// 		if (!line)
// 			break ;
// 		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
// 			&& ft_strlen(limiter) == ft_strlen(line) - 1)
// 			break ;
// 		if (p == 1)
// 			write(*fd_in, line, ft_strlen(line));
// 		free(line);
// 	}
// 	if (p == 1)
// 		dup2(fd, 0);
// 	close(fd);
// 	free(line);
// }

// int	get_max_in(t_red *red)
// {
// 	int max_in;

// 	if (!red)
// 		return (-1);
// 	max_in = red->index;
// 	while (red)
// 	{
// 		if (ft_strncmp(red->type, "<<", 3) == 0 || ft_strncmp(red->type, "<", 2) == 0)
// 		{
// 			if (red->index >= max_in)
// 				max_in = red->index;	
// 		}
// 		red = red->next;
// 	}
// 	return (max_in);
// }

// int	get_max_out(t_red *red)
// {
// 	int max_out;
	
// 	if (!red)
// 		return (-1);
// 	max_out = red->index;
// 	while (red)
// 	{
// 		if (ft_strncmp(red->type, ">>", 3) == 0 || ft_strncmp(red->type, ">", 2) == 0)
// 		{
// 			if (red->index >= max_out)
// 				max_out = red->index;	
// 		}
// 		red = red->next;
// 	}
// 	return (max_out);
// }

void	handle_rederection(t_red *red_node)
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
		if (ft_strncmp(red_node->type, "<<", 3) == 0 || ft_strncmp(red_node->type, "<", 2) == 0)
		{
			if (ft_strncmp(red_node->type, "<<", 3) == 0)
			{
				dup2(*(red_node)->fd_herdoc, 1);
				close(*(red_node)->fd_herdoc);
			}
			else
			{
					fd_in = open(red_node->red, O_RDONLY, 0644);
					if (fd_in < 0)
					{
						if (red_node->expaind == 1)
							printf("minishell: %s: ambiguous redirect\n", red_node->exp);
						else
							printf("minishell: %s: No such file or directory\n", red_node->red);
						exit(1);
					}
					dup2(fd_in, 1);
					close(fd_in);
			}
		}
		else if (ft_strncmp(red_node->type, ">>", 3) == 0 || ft_strncmp(red_node->type, ">", 2) == 0)
		{
			if (ft_strncmp(red_node->type, ">>", 3) == 0)
			{
					fd_out = open(red_node->red, O_CREAT, O_RDWR, O_APPEND, 0644);
					if (fd_out < 0)
					{
						if (red_node->expaind == 1)
							printf("minishell: %s: ambiguous redirect\n", red_node->exp);
						exit(1);
					}
			}
			else
			{
					fd_out = open(red_node->red, O_CREAT, O_RDWR, O_TRUNC, 0644);
					if (fd_out < 0)
					{
						if (red_node->expaind == 1)
							printf("minishell: %s: ambiguous redirect\n", red_node->exp);
						exit(1);
					}
			}
			dup2(fd_out, 0);
			close(fd_out);
		}
		red_node = red_node->next;
	}
}

//***************************************
// t_red	*get_red_nod(void)
// {
// 	t_red *node;
// 	// char *cmd[3] = {"ls -la", "grep Makefile", "wc -lwc"};
// 	node = NULL;
// 	int i = -1;
// 		ft_lstadd_back_red(&node, ft_lstnew_red("<", "Makefile"));
// 		ft_lstadd_back_red(&node, ft_lstnew_red(">", "test1"));
// 		ft_lstadd_back_red(&node, ft_lstnew_red("<", "test2", 3));
// 	display_red(node);
// 	return (node);
// }

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

#include <string.h>

void make_process(t_node *node, int *fd_out)
{
	int pid;
	int fd[2];

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		if (!strcmp(node->cmd_node[0], "wc"))
		{
			printf("tetse\n");
			dup2(*fd_out, 1);
			close(*fd_out);
		}
		else
		{
			dup2(fd[1], 1);
			close(fd[1]);
		}
		execve(node->cmd_node[0], node->cmd_node, NULL);	
		exit(1);
	}
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	printf("parent\n");
}

//*****************************************

void	ft_minishell(t_env **env, char **cmd)
{
	t_node	*pipe_node;
	t_path	data;
	t_var	var;
	char	*line;
	int		size;
	// int		fdd[2];
	// int		*fd;
	int		pid;
	int		i;
	int b;
	
	line = NULL;
	while (1)
	{
		i = 0;
		var.status = 0;
		line = readline("minishell$ ");
		if (!line)
			break ;
		add_history(line);
		rl_redisplay();
		pipe_node = NULL;
		ft_initialis_data(&data, *env, 0, 0);
		//get pipe_node [cmd[][], red[][]] -> [cmd[][], red[][]] -> [cmd[][], red[][]] -> [cmd[][], red[][]];
		// if (!pipe_node)
		// 	continue ;
		// size = size_pipe_node(pipe_node);
		// char *cm[3] = {"ls -l", "grep Makefile", "wc"};
		cmd = ft_splith(line, ' ');
		if (!cmd)
			continue ;
			
		t_node *node =  malloc(sizeof(t_node));
		if (!node)
			continue ;
		// node = get_pars();
		// printf("\n789\n");
		size = 1; // hadi ghi bach njarab node whda
		if (size == 1)
		{
			handle_rederection(node->red_node);
			b = built_functions(env, &var, cmd);
			if (b == -1)
			{
				pid = fork();
				if (pid == 0)
					ft_exuctute(cmd, &data, &var);
				// wait(NULL);
				//===========
				int i = -1;
				// int fd_out = open("dev", O_CREAT | O_RDWR | O_APPEND, 0644);
				// while(node)
				// {
				// 	// make_process(node, &fd_out);
				// 	node = node->next;
				// 	i++;
				// }
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
	ft_minishell(&env, cmd);
	return (0);
}
