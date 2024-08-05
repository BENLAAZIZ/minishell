/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:04:25 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/05 11:05:06 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_red(t_red_node *red)
{
	if (!red)
		return ;
	while (red)
	{
		printf("\n [%s %s] ", red->red, red->file);
		red = red->next;
	}
}

void	display_node(t_cmd_node *node)
{
	if (!node)
		return ;
	while (node)
	{
		printf("\n-----------------------------------\n");
		display_red(node->red_node);
		printf("\n {%s} ", node->command[0]);
		printf("\n-----------------------------------\n");
		node = node->next;
	}
}
