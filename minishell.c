/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:35:52 by hben-laz          #+#    #+#             */
/*   Updated: 2024/07/07 19:22:51 by hben-laz         ###   ########.fr       */
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

void	here_doc(char *limiter, int *fd_in, int fd)
{
	char	*line;

	*fd_in = open("herd.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
	fd = open("herd.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
	if (*fd_in == -1 || fd == -1)
		return (ft_error("open fail : \n", "fail", 0, -1));
	unlink("herd.txt");
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& ft_strlen(limiter) == ft_strlen(line) - 1)
			break ;
		write(*fd_in, line, ft_strlen(line));
		free(line);
	}
	dup2(fd, 0);
	close(fd);
	free(line);
}

void	handle_rederection(t_node	*pipe_node)
{
	int		fd;
	int		fd_in;
	int		fd_out;
	
	fd_in = -1;
	fd = -1;
	if (!pipe_node)
		return ;
	while (pipe_node->red_node)
	{
		if (ft_strncmp(pipe_node->red_node->type, "<<", 3) == 0)
			here_doc(pipe_node->red_node->red, &fd_in, fd);
		else if (ft_strncmp(pipe_node->red_node->type, "<", 2) == 0)
			fd_in = open(pipe_node->red_node->red, O_RDONLY, 0777);
		else if (ft_strncmp(pipe_node->red_node->type, ">", 2) == 0)
			fd_out = open(pipe_node->red_node->red, O_CREAT, O_RDWR, O_TRUNC, 0777);
		else if (ft_strncmp(pipe_node->red_node->type, ">>", 3) == 0)
			fd_out = open(pipe_node->red_node->red, O_CREAT, O_RDWR, O_APPEND, 0777);
		pipe_node->red_node = pipe_node->red_node->next;
	}
	dup2(fd_in, 0);
	dup2(fd_out, 1);
	close (fd_in);
	close (fd_out);
}

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
		cmd = ft_splith(line, ' ');
		if (!cmd)
			continue ;
		size = 1; // hadi ghi bach njarab node whda
		if (size == 1)
		{
			handle_rederection(pipe_node);
			b = built_functions(env, &var, cmd);
			if (b == -1)
			{
				pid = fork();
				if (pid == 0)
					ft_exuctute(cmd, &data, &var);
			}
		}
		// else
		// {
		// 	// while i < size : pipe_node = pipe_node->next -->
		// 	while (i < size)
		// 	{
				
		// 		handle_pipe(data, env);// mmmmm
		// 		pid = fork();
		// 		// handle_file_rederection(pipe_node.red, fd);
		// 		b = built_functions(env, &var, cmd);
		// 		if (pid == -1)
		// 		{
		// 			perror("pid fail :"), close_fd(fd);
		// 			i++;
		// 			continue ;
		// 		}
		// 		else if (pid == 0 && built_functions(env, &var, cmd) == -1)
	
		// 			printf("\nexcution her  with fork\n");
		// 			// ft_exuctute(cmd, &data, &var);
		// 		i++;
		// 	}
			
		// }
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
