/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:43:22 by hben-laz          #+#    #+#             */
/*   Updated: 2024/07/24 11:45:38 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *s, char *flag, int i, int in)
{
	if (ft_strncmp(flag, "fail", 4) != 0 && i == 1)
	{
		write(2, flag, ft_strlen(flag));
		write(2, s, ft_strlen(s));
		write(2, "\n", 1);
		if (in == -1)
			return ;
	}
	else if (ft_strncmp(flag, "fail", 4) != 0 && i == 0)
	{
		write(2, s, ft_strlen(s));
		write(2, flag, ft_strlen(flag));
		write(2, "\n", 1);
		if (in == -1)
			return ;
	}
	else
	{
		write(2, s, ft_strlen(s));
		write(2, "\n", 1);
	}
}

void	free_t_split(char **array)
{
	int	i;

	i = 0;
	if (!array || !*array)
		return ;
	while (array && array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	close_fd(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	wait_function(int c, t_variable *varr)
{
	int	status;

	while (c--)
	{
		if (wait(&status) == varr->id)
		{
			varr->var.status = status;
			if (WIFEXITED(varr->var.status))
				varr->var.status = WEXITSTATUS(varr->var.status);
		}
	}
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if ((unsigned char)c == '\0')
		return ((char *)s + ft_strlen(s));
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}
