/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:41:43 by hben-laz          #+#    #+#             */
/*   Updated: 2024/07/18 15:48:09 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	check_special_char_export(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (!((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' && str[0] <= 'Z') || str[i] == '_'))
			return (0);
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_')
			i++;
		else
			return (0);
	}
	return (1);
}

void	export_suit(t_env **env, t_var	*var, char *str)
{	
	t_env	*node;	
	t_env	*exp;
	char	*tmp;

	node = point_node(*env, var->var);
	if (!node)
	{
		exp = ft_lstnew(var->var, var->val);
		ft_lstadd_back(env, exp);
	}
	else
	{
		if (var->egal == 1)
		{
			tmp = node->value;
			node->value = ft_strjoin(tmp, var->val);
			free(tmp);
		}
		else if(var->egal == -1)
		{
			printf("minishell: export: `%s': not a valid identifier\n", str);
			var->status = 1;
		}
		else
			if (node->variable && var->val)
				node->value = var->val;
	}
}

void	export(t_env **env , char **cmd, int i, t_var *var)
{
	var->egal = 0;
	var->status = 0;
	if (!cmd[1])
		display_list_export(*env);
	else
	{
		while (cmd[i])
		{
			var->var = get_variabl_export(cmd[i], &var->egal);
			var->val = get_value(cmd[i]);
			if (check_special_char_export(var->var) == 0 || !var || var->egal == -1)
			{
				printf("minishell: export: `%s': not a valid identifier\n", cmd[i]);
				i++;
				var->status = 1;
				continue ;
			}
			else
				export_suit(env, var, cmd[i]);
			i++;
		}
	}
}
