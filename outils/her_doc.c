/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:49:43 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/14 13:35:20 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	open_file_herd(t_box *box, int *fd_herd, t_word *token, int *fd)
{
	token->line = NULL;
	token->next = NULL;
	token->old_word = NULL;
	*fd_herd = open("herd.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
	*fd = open("herd.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
	if (*fd == -1)
		return (close(*fd_herd),
			ft_error("open fail : \n", "fail", 0, -1), -1);
	if (*fd_herd == -1)
		return (close(*fd), ft_error("open fail : \n", "fail", 0, -1), -1);
	ad_array_fd(box, *fd_herd, 0);
	ad_array_fd(box, *fd, 0);
	unlink("herd.txt");
	return (0);
}

void	ad_array_fd(t_box *box, int fd, int i)
{
	if (i == 0)
	{
		box->array_fd[box->i + 1] = fd;
		box->i = box->i + 1;
	}
	if (i == 1)
	{
		box->array_fd[box->i] = box->fd[0];
		box->array_fd[box->i + 1] = box->fd[1];
		box->i = box->i + 2;
	}
}

int	ctl_handler(t_box *box, int *fd_herd, t_word *token, int fd)
{
	box->var.status = 1;
	ad_array_fd(box, fd, 0);
	ad_array_fd(box, *fd_herd, 0);
	(dup2(box->fd_stdin, 0), close(*fd_herd));
	signal(SIGINT, handle_siginit);
	return (free_array_fd(box), free(token->line), free(token), -1);
}

int	here_doc(t_node *node, t_env *env, t_box *box)
{
	t_word	*token;
	int		fd;

	token = (t_word *)malloc(sizeof(t_word));
	if (token == NULL)
		return (0);
	if (open_file_herd(box, &node->fd_herd, token, &fd) == -1)
		return (-1);
	signal(SIGINT, signlas_heredoc);
	while (1)
	{
		token->line = readline("> ");
		if (check_limiter(token, env, box->l, box->l_nq) == 1)
			break ;
		write(fd, token->line, ft_strlen(token->line));
		(write(fd, "\n", 1), free(token->line), free(token->old_word));
	}
	if (g_get_status)
	{
		if (ctl_handler(box, &node->fd_herd, token, fd) == -1)
			return (-1);
	}
	signal(SIGINT, handle_siginit);
	return (close(fd), free(token->line), free(token), 0);
}
