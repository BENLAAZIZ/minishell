/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:52:36 by aaaraba           #+#    #+#             */
/*   Updated: 2024/08/10 10:25:38 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_char(char c)
{
	if (c == '|')
		return ("|");
	if (c == '>')
		return (">");
	if (c == '<')
		return ("<");
	return (NULL);
}

int	ft_is_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	check_char_expand(char c)
{
	if (c == 32 || (c >= 9 && c <= 13) || c == '|'
		|| c == '>'
		|| c == '<'
		|| c == '"'
		|| c == '='
		|| c == '$'
		|| c == '\''
		|| c == '\0')
		return (0);
	return (1);
}

int	char_stop(t_word *token, t_env **env)
{
	int	length;

	length = dollar_length(token, env);
	if (length % 2 != 0)
	{
		(*env)->i--;
		return (1);
	}
	else if (token->value[(*env)->i] == '\0')
		return (1);
	return (0);
}
