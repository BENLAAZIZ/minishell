/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaaraba <aaaraba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:38:00 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/04 16:41:21 by aaaraba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_terminal_attr(struct termios *original_termios)
{
	tcgetattr(STDIN_FILENO, original_termios);
	original_termios->c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, original_termios);
}

void	restore_terminal_attributes(struct termios *original_termios)
{
	tcsetattr(STDIN_FILENO, TCSANOW, original_termios);
}

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
	}
	if (sig == SIGQUIT)
		return ;
}
