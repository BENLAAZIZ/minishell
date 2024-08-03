/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 14:59:21 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/03 15:00:07 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int ft_pars(t_variable *varr, t_env **env)
{
	if (check_quotes(varr->line) == 1)
	{
		free_data(varr);
		return (-1);
	}
	varr->token = ft_list_tokn(varr->line, varr->token, *env);
	if (!varr->token)
	{
		free_data(varr);
		return (-1); 
	}
	word_expand(varr->token, *env, varr);
	if (remove_quotes(varr->token, 0, 0, 0) == 0)
	{
		varr->var.status = 1;
		ft_lstclear_token(&varr->token);
		free(varr->line);
		return (-1);
	}
	return (0);
}

int	check_empty_line(t_variable *varr, t_env **env)
{
	if (!varr->line)
	{
		write(1, "exit\n", 5);
		free_data(varr);
		ft_lstclear_env(env);
		rl_clear_history();
		exit(varr->var.status);
	}
	if (varr->line[0] == '\0')
	{
		free_data(varr);
		rl_clear_history();
		return (-1); 
	}
	add_history(varr->line);
	rl_redisplay(); 
	return (0);
}

