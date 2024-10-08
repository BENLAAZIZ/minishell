/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:01:32 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/13 17:10:44 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	chek_permession(char *str, int is_exp, char *expand, int i)
{
	struct stat	st;
	int			ret;
	char		**array;

	if (is_exp)
	{
		array = ft_splith(str, ' ');
		if (array && array[1])
			return (free_t_split(array), ft_perror_h(expand, OMB_R), -1);
	}
	ret = stat(str, &st);
	if (!str[0] && is_exp == 1)
		return (ft_perror_h(str, OMB_R), -1);
	if (ret == -1)
		return (0);
	else
	{
		if (S_ISDIR(st.st_mode))
			return (ft_perror_h(str, IS_D), -1);
		else if (access(str, R_OK) && i == 0)
			return (ft_perror_h(str, PRM_D), -1);
		else if (access(str, W_OK) && i == 1)
			return (ft_perror_h(str, PRM_D), -1);
	}
	return (0);
}

int	case_input_red(t_red_node *red_node, int *fd_herd)
{
	int	fd_in;

	fd_in = -1;
	if (ft_strncmp(red_node->red, "<<", 3) == 0)
		fd_in = *fd_herd;
	else
	{
		if (chek_permession(red_node->file, red_node->expand,
				red_node->exp, 0) == -1)
			return (-1);
		fd_in = open(red_node->file, O_RDONLY, 0644);
		if (fd_in < 0)
		{
			if (red_node->expand == 1)
				ft_perror_h(red_node->exp, OMB_R);
			else
				ft_perror_h(red_node->file, NO_F);
			return (-1);
		}
	}
	dup2(fd_in, 0);
	close(fd_in);
	return (0);
}

int	case_output_red(t_red_node *red_node, int *flag)
{
	int	fd_out;

	fd_out = -1;
	if (chek_permession(red_node->file, red_node->expand,
			red_node->exp, 1) == -1)
		return (-1);
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
			ft_perror_h(red_node->exp, OMB_R);
		return (-1);
	}
	dup2(fd_out, 1);
	close(fd_out);
	return (0);
}

int	handle_redirection(int *flag, t_red_node *red_node, int	*fd_herd)
{
	if (!red_node)
		return (0);
	while (red_node)
	{
		if (ft_strncmp(red_node->red, "<<", 2) == 0
			|| ft_strncmp(red_node->red, "<", 2) == 0)
		{
			if (case_input_red(red_node, fd_herd) == -1)
				return (-1);
		}
		else if (ft_strncmp(red_node->red, ">>", 3) == 0
			|| ft_strncmp(red_node->red, ">", 2) == 0)
		{
			if (case_output_red(red_node, flag) == -1)
				return (-1);
		}
		red_node = red_node->next;
	}
	return (1);
}

int	check_redirection(t_box *box)
{
	int	c;

	c = handle_redirection(&box->node->flag_r,
			box->node->red_node, &box->node->fd_herd);
	if (c == -1)
	{
		box->var.status = 1;
		return (-1);
	}
	return (0);
}
