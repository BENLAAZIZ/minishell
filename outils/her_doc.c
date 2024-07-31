/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:49:43 by hben-laz          #+#    #+#             */
/*   Updated: 2024/07/31 16:44:23 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		close(0);
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
	token->line = NULL;
	token->next = NULL;
	node->fd_herd = open("herd.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
	fd = open("herd.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (close(node->fd_herd),
			ft_error("open fail : \n", "fail", 0, -1));
	if (node->fd_herd == -1)
		return (close(fd), ft_error("open fail : \n", "fail", 0, -1));
	unlink("herd.txt");
	while (1)
	{
		signal(SIGINT, signlas_heredoc);
		token->line = readline("> ");
		if (check_limiter(token, env, l, l_nq) == 1)
			break ;
		write(fd, token->line, ft_strlen(token->line));
		(write(fd, "\n", 1), free(token->line));
	}
	(close(fd), free(token->line));
}
