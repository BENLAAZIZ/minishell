/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:49:43 by hben-laz          #+#    #+#             */
/*   Updated: 2024/07/24 10:52:51 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	here_doc(char *limiter, t_cmd_node *node)
{
	char	*line;
	int		fd;

	node->fd_herd = open("herd.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
	fd = open("herd.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (close(node->fd_herd), ft_error("open fail : \n", "fail", 0, -1));
	if (node->fd_herd == -1)
		return (close(fd), ft_error("open fail : \n", "fail", 0, -1));
	unlink("herd.txt");
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& ft_strlen(limiter) == ft_strlen(line))
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	// close(node->fd_herd);
	close(fd);
	free(line);
	// dprintf(2,"fd herdoc in herdoc = %d\n", node->fd_herd);
	// dprintf(2, "fd = %d\n", fd);
}
