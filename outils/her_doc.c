/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:49:43 by hben-laz          #+#    #+#             */
/*   Updated: 2024/07/28 19:57:49 by hben-laz         ###   ########.fr       */
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

void	here_doc(char *limiter, char *limiter_nq, t_cmd_node *node, t_env *envirement)
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
		token->line = readline("> ");
		if (!token->line)
			break ;
		if (ft_strncmp(token->line, limiter_nq, ft_strlen(limiter_nq)) == 0
			&& ft_strlen(limiter_nq) == ft_strlen(token->line))
			break ;
		if (is_quote(limiter) == 0)
			word_expand_her(token, envirement);
		write(fd, token->line, ft_strlen(token->line));
		write(fd, "\n", 1);
		free(token->line);
	}
	close(fd);
	free(token->line);
}

// void	here_doc(char *limiter, t_cmd_node *node)
// {
// 	char	*line;
// 	int		fd;

// 	node->fd_herd = open("herd.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
// 	fd = open("herd.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
// 	if (fd == -1)
// 		return (close(node->fd_herd),
// 			ft_error("open fail : \n", "fail", 0, -1));
// 	if (node->fd_herd == -1)
// 		return (close(fd), ft_error("open fail : \n", "fail", 0, -1));
// 	unlink("herd.txt");
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line)
// 			break ;
// 		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
// 			&& ft_strlen(limiter) == ft_strlen(line))
// 			break ;
// 		write(fd, line, ft_strlen(line));
// 		write(fd, "\n", 1);
// 		free(line);
// 	}
// 	close(fd);
// 	free(line);
// }

