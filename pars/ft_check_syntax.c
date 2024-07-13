#include "minishell.h"

void	print_error(char *token)
{
	printf("syntax error near unexpected token `%s'\n", token);
}

int	check_quotes(char *line)
{
	int	sign;
	int	i;

	i = 0;
	sign = 0;
	while (line[i] != '\0')
	{
		ft_check_quotes(line[i], &sign);
		i++;
	}
	if (sign == 1)
		return (free(line), print_error("'"), 1);
	if (sign == 2)
		return (free(line), print_error("\""), 1);
	return (0);
}

int	check_red(int type)
{
	if ((type == L_RED
			|| type == R_RED
			|| type == DR_RED
			|| type == DL_RED))
	{
		return (1);
	}
	return (0);
}

int	check_token(int type)
{
	if (type == L_RED)
		return (print_error("<"), 1);
	else if (type == R_RED)
		return (print_error(">"), 1);
	else if (type == DL_RED)
		return (print_error("<<"), 1);
	else if (type == DR_RED)
		return (print_error(">>"), 1);
	return (0);
}

int	check_syntax(t_word *token)
{
	t_word *tmp;

	tmp = token;
	if (token == NULL)
		return (1);
	if (token->type == PIPE)
		return (print_error("|"), 1);
	while (token != NULL)
	{
		if ((token->type == PIPE && token->next == NULL)
			|| (token->type == PIPE && token->next->type == PIPE))
			return (print_error("|"), 1);
		if (check_red(token->type) == 1 && token->next == NULL)
			return (print_error("newline"), 1);
		if (token->next != NULL)
		{
			if ((check_red(token->next->type)) == 1)
			{
				if (check_red(token->next->type) == 1
					&& check_red(token->type) == 1)
					return (print_error(token->next->value), 1);
				if ((check_token(token->type)) == 1)
					return (1);
			}
			if (token->next->type == PIPE && check_red(token->type) == 1)
				return (print_error("|"), 1);
			if (token->type == PIPE && check_red(token->next->type) == 1
				&& token->next->next == NULL)
				return (print_error("newline"), 1);
		}
		token = token->next;
	}
	token = tmp;
	return (0);
}
