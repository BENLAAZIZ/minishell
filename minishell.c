/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:35:52 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/02 20:51:10 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    get_terminal_attr(struct termios *original_termios)
{
    tcgetattr(STDIN_FILENO, original_termios);
    original_termios->c_lflag &= ~ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, original_termios);
}

void    restore_terminal_attributes(struct termios *original_termios)
{
    tcsetattr(STDIN_FILENO, TCSANOW, original_termios);
}


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

int t = 0;
void	ft_minishell(t_env **env, t_variable *varr, struct termios *term)
{
	while (1)
	{
		ft_initialis_data(varr, *env, 0, 0);
		(dup2(varr->fd_stdin, 0), dup2(varr->fd_stdout, 1));
		varr->line  = readline("minishell$ ");
		if (!varr->line)
		{
			write(1, "exit\n", 5);
			free_data(varr);
			ft_lstclear_env(env);
			rl_clear_history();
			close(varr->fd_stdin);
			close(varr->fd_stdout);
			exit(varr->var.status);
		}
		if (varr->line[0] == '\0')
		{
			free_data(varr);
			rl_clear_history();
			close(varr->fd_stdin);
			close(varr->fd_stdout);
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
		if (!varr->token)
		{
			free_data(varr);
			continue ; 
		}
		word_expand(varr->token, *env, varr);
		// if (varr->token->value)
		// {
		// 	ft_lstclear_token(&varr->token);
		// 	free_data(varr);
		// 	continue ; 
		// }
		// exit(0);
		if (remove_quotes(varr->token, 0, 0, 0) == 0)
		{
			varr->var.status = 1;
			ft_lstclear_token(&varr->token);
			free(varr->line);
			continue ;
		}
		if (execute_line(env, varr) == -1)
		{
			ft_lstclear_cmd(&varr->node);
			ft_lstclear_token(&varr->token);
			free_data(varr);
			continue ;
		}
		free_data(varr);
		restore_terminal_attributes(term);
		ft_lstclear_cmd(&varr->node);
		ft_lstclear_token(&varr->token);
	} 
	close(3);
	close(4);
	ft_lstclear_token(&varr->token);
	ft_lstclear_env(env);
	ft_lstclear_cmd(&varr->node);   
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
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGQUIT)
		return ;
}



int	main(int argc, char *argv[], char **ev)
{
	t_variable	varr;
	t_env		*env;
	struct termios    original_termios;
	get_terminal_attr(&original_termios);
	// atexit(v);
	(void)argc;
	(void)argv;
	rl_catch_signals = 0;
	signal(SIGINT, handle_siginit);
	signal(SIGQUIT, handle_siginit);
	// varr.node = NULL;
	// varr.token = NULL;
	// varr.line = NULL;
	env = NULL;
	varr.fd_stdin = dup(0);
	varr.fd_stdout = dup(1);
	varr.var.status = 0;
	ft_env(ev, &env);  
	ft_minishell(&env, &varr, &original_termios);
	return (0);
}
