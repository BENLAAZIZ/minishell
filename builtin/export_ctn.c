/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_ctn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:26:02 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/09 15:55:42 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	display_list_export(t_env *a)
{
	while (a)
	{
		if (!a->value)
			printf("declare -x %s\n", a->variable);
		else if (ft_strncmp(a->variable, "_", 2) == 0)
		{
			a = a->next;
			continue ;
		}
		else
			printf("declare -x %s=\"%s\"\n", a->variable, a->value);
		a = a->next;
	}
}

void	check_get_variabl(char *line, int *egal, char *variable, int *i)
{
	if (line == NULL)
		return ;
	while (line[*i])
	{
		if (line[*i] == '+' || line[*i] == '=')
		{
			if (line[*i] == '+' && line[*i + 1] == '=')
				*egal = 1;
			else if (line[*i] == '+' && line[*i + 1] != '=')
				*egal = -1;
			else
				*egal = 0;
			break ;
		}
		variable[*i] = line[*i];
		(*i)++;
	}
}

char	*get_variabl_export(char *line, int *egal)
{
	int		i;
	char	*variable;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i] && (line[i] != '='))
		i++;
	if (i == 0)
		return (NULL);
	variable = (char *)malloc(i + 1);
	if (!variable)
		return (NULL);
	i = 0;
	check_get_variabl(line, egal, variable, &i);
	variable[i] = '\0';
	return (variable);
}
