#include "minishell.h"

int lenght_no_quotes(t_word *token)
{
	int quotes = 0;
	int sign = 0;
	int i = 0;
	int length = strlen(token->value);

	if (token->value[0] != '"')
    {
		if (token->value[length - 1] == '"')
			sign = 2;
    }
	ft_check_quotes(token->value[i], &sign);
	while (token->value[i] != '\0')
		{
			if (sign == 1 && token->value[i] == '\'')
				quotes++;
			if (sign == 2 && token->value[i] == '"')
				quotes++;
			i++;
		}
	return (quotes);
}

int remove_quotes(t_word *token)
{ 
	if (token == NULL || token->value == NULL)
		return (0);
	t_word *tmp = token;
	int	sign;
	int	i;
	int	j;
	int length = 0;
	while (token)
	{
		length = strlen(token->value);
		i = 0;
		j = 0;
		sign = 0;
		i = 0;
		token->val_noquotes = malloc((length - lenght_no_quotes(token)) + 1);
		token->quotes_type = 0;
		while (token->value[i] != '\0')
		{
			ft_check_quotes(token->value[i], &sign);
				if (sign != 2 && token->value[i] == '\'')
				{
					token->quotes_type = 1;
					i++;
				}
				else if (sign != 1 && token->value[i] == '"')
				{
					token->quotes_type = 2;
					i++;
				}
				else
				{
					token->val_noquotes[j] = token->value[i];
					j++;
					i++;
				}
				if (token->value[i] == '\0')
					break;
		}
		token->val_noquotes[j] = '\0';
		token = token->next;
	}
	token = tmp;
	while(tmp != NULL)
	{
		printf("%s\n", tmp->val_noquotes);
		tmp = tmp->next;
	}
	return (0);
}