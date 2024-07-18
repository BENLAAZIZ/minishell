/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:01:32 by hben-laz          #+#    #+#             */
/*   Updated: 2024/07/18 18:02:16 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	handle_redirection(int *flag, t_red_node *red_node)
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
						if (red_node->expand == 1)
							printf("minishell: %s: ambiguous redirect\n", red_node->exp);
						else
							printf("minishell: %s: No such file or directory \n", red_node->file);
						return (-1);
					}
					dup2(fd_in, 0);
					close(fd_in);
			}
		}
		else if (ft_strncmp(red_node->red, ">>", 3) == 0 || ft_strncmp(red_node->red, ">", 2) == 0)
		{
			if (ft_strncmp(red_node->red, ">>", 3) == 0)
			{
					*flag = 1;
					fd_out = open(red_node->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
			}
			else
			{
					*flag = 1;
					fd_out = open(red_node->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			}
			if (fd_out < 0)
			{
				if (red_node->expand == 1)
					printf("minishell: %s: ambiguous redirect\n", red_node->exp);
				return (-1);
			}
			dup2(fd_out, 1);
			close(fd_out);
		}
		red_node = red_node->next;
	}
	return (1);
}