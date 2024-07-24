/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:01:32 by hben-laz          #+#    #+#             */
/*   Updated: 2024/07/24 10:53:33 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	case_input_red(t_red_node *red_node, int *fd_herd)
{
	int	fd_in;

	fd_in = -1;
	// *fd_herd = *fd_herd;
	if (ft_strncmp(red_node->red, "<<", 3) == 0)
	{
		// dprintf(2, "in redirection \n");
		// dprintf(2, "fd_herd in handel red = %d\n", *fd_herd);
		// fd_in = open("herd.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
		// unlink("herd.txt");
		dup2(*fd_herd, 0);
		close(*fd_herd);
		// dup2(fd_in, 0);
		// close(fd_in);
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
	return (0);
}

int	case_output_red(t_red_node *red_node, int *flag)
{
	int	fd_out;
	
	fd_out = -1;
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
	return (0);
}

int	handle_redirection(int *flag, t_red_node *red_node, int	*fd_herd)
{
	if (!red_node)
		return 0;
	while (red_node)
	{
		if (ft_strncmp(red_node->red, "<<", 2) == 0 || ft_strncmp(red_node->red, "<", 2) == 0)
		{
			if (case_input_red(red_node, fd_herd) == -1)
				return (-1);
		}
		else if (ft_strncmp(red_node->red, ">>", 3) == 0 || ft_strncmp(red_node->red, ">", 2) == 0)
		{
			if (case_output_red(red_node, flag) == -1)
				return (-1);
		}
		red_node = red_node->next;
	}
	return (1);
}
