/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:33:32 by aaaraba           #+#    #+#             */
/*   Updated: 2024/08/10 10:31:43 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_in_child(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "", 1);
	}
	if (sig == SIGQUIT)
		return ;
}

void	handle_siginit(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_get_status = 1;
	}
	if (sig == SIGQUIT)
		return ;
}

void	signlas_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		signal_hdoc(1);
		g_get_status = 1;
		close (0);
	}
}

int	signal_hdoc(int check)
{
	static int	signal;

	if (check == 1)
		signal = 1;
	else if (check == 0)
		signal = 0;
	return (signal);
}
