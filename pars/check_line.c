/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:56:47 by aaaraba           #+#    #+#             */
/*   Updated: 2024/08/05 10:29:01 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_quotes(char c, int *sign)
{
	if (c == '"' && *sign == 2)
		*sign = 0;
	else if (c == '\'' && *sign == 1)
		*sign = 0;
	else if (c == '"' && *sign == 0)
		*sign = 2;
	else if (c == '\'' && *sign == 0)
		*sign = 1;
	return (0);
}
