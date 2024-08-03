/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:49:43 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/03 13:15:15 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_signal = 1;

int	is_quote(char *limiter)
{
	int	i;

	i = 0;
	while (limiter[i])
	{
		if (limiter[i] == '\'' || limiter[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

void	signlas_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		check_signal = 0;
		close (0);
	}
}

int	check_limiter(t_word	*token, t_env *env, char *l, char *l_nq)
{
	if (!token->line)
		return (1);
	if (ft_strncmp(token->line, l_nq, ft_strlen(l_nq)) == 0
		&& ft_strlen(l_nq) == ft_strlen(token->line))
		return (1);
	if (is_quote(l) == 0)
		word_expand_her(token, env);
	return (0);
}

void	here_doc(char *l, char *l_nq, t_cmd_node *node, t_env *env)
{
	t_word	*token;
	int		fd;

	token = (t_word *)malloc(sizeof(t_word));
	if (token == NULL)
		return ;
	token->line = NULL;
	token->next = NULL;
	token->old_word = NULL;
	node->fd_herd = open("herd.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
	fd = open("herd.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (close(node->fd_herd),
			ft_error("open fail : \n", "fail", 0, -1));
	if (node->fd_herd == -1)
		return (close(fd), ft_error("open fail : \n", "fail", 0, -1));
	unlink("herd.txt");
	signal(SIGINT, signlas_heredoc);
	while (1)
	{
		if (check_signal == 0)
			break;
		token->line = readline("> ");
		if (token->line == NULL) 
			close(0);
		if (check_signal == 0)
		{
			close(0);
			break;
		}
		if (check_limiter(token, env, l, l_nq) == 1)
			break ;
		write(fd, token->line, ft_strlen(token->line));
		(write(fd, "\n", 1), free(token->line), free(token->old_word));
	}
	check_signal = 1;
	signal(SIGINT, handle_siginit);
	(close(fd), free(token->line));
	free(token);
}
