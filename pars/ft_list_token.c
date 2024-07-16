#include "minishell.h"

int dollar_size(char *all_command)
{
	int	sign;
	int	i;
	int	size;
	int lenght;

	lenght = 0;
	i = 0;
	sign = 0;
	while (all_command[i])
	{
		size = 0;
		ft_check_quotes(all_command[i], &sign);
		if (all_command[i] == '$')
		{
			while (all_command[i] == '$' && sign != 1)
			{
				ft_check_quotes(all_command[i], &sign);
				size++;
				i++;
			}
			ft_check_quotes(all_command[i], &sign);
			if (sign == 2 && size % 2 != 0)
			{
				if (all_command[i] != '"')
					lenght++;
			}
			else if (sign != 1 && size % 2 != 0)
				lenght++;
			if (size % 2 == 0 && sign != 1)
				lenght += 2;
		}
		lenght++;
		i++;
	}
	return (lenght);
}

char *remove_dollar(char *all_command)
{
	int		sign;
	char	*escap_dollar;
	int		size;
	int		i;
	int		j;

	j = 0;
	i = 0;
	sign = 0;
	escap_dollar = malloc((sizeof(char *) * dollar_size(all_command)) + 1);
	while (all_command[i])
	{
		size = 0;
		ft_check_quotes(all_command[i], &sign);
		if (all_command[i] == '$')
		{
			while (all_command[i] == '$' && sign != 1)
			{
				ft_check_quotes(all_command[i], &sign);
				size++;
				i++;
			}
			ft_check_quotes(all_command[i], &sign);
			if (sign == 2 && size % 2 != 0)
			{
				if (all_command[i] != '"')
					escap_dollar[j++] = '$';
			}
			else if (sign != 1 && size % 2 != 0)
				escap_dollar[j++] = '$';
			if (size % 2 == 0 && sign != 1)
			{
				escap_dollar[j++] = '$';
				escap_dollar[j++] = '$';
			}
		}
		escap_dollar[j++] = all_command[i];
		i++;
	}
	escap_dollar[j] = '\0';
	return (escap_dollar);
}


char *copy_in_word(char *escap_dollar, t_env *envirment, int *sign)
{
	int	size;
	t_word	*word;

	size = envirment->i;
	word = NULL;
	while (ft_is_space(escap_dollar[envirment->i]) == 1 && escap_dollar[envirment->i])
			envirment->i++;
	while (escap_dollar[envirment->i])
	{
		if (*sign != 1 && end_point(escap_dollar[envirment->i], sign) == 0 && size != envirment->i)
			break;
		ft_check_quotes(escap_dollar[envirment->i], sign);
		envirment->i++;
	}
	if (envirment->sub == NULL)
		envirment->sub = ft_substr(escap_dollar, size, envirment->i - size);
	return (envirment->sub);
}

int check_dollar_sign(char c1, char c2, char c3)
{
	if ((c1 == '$' && check_char_expand (c2) == 1) ||
			(c1 == '"' && c2 == '$' && check_char_expand(c3) == 1))
		return (1);
	return (0);
}

t_word	*ft_list_tokn(char *all_command, t_word *token, t_env *envirment)
{
	char	*escap_dollar;
	int		sign;
	t_word	*word;
	t_env 	*env_node;

	word = NULL;
	env_node = NULL;
	sign = 0;
	envirment->i = 0;
	envirment->expand = NULL;
	envirment->sub = NULL;
	escap_dollar = remove_dollar(all_command);
	
	while (escap_dollar[envirment->i] != '\0')
	{

		while (ft_is_space(escap_dollar[envirment->i]) == 1 && escap_dollar[envirment->i] && sign == 0)
			envirment->i++;  // escap_dollar[envirment->i] != '\0'
		if (escap_dollar[envirment->i] == '\0')
			break ;  
		if (sign == 0 && ((escap_dollar[envirment->i] == '>' && escap_dollar[envirment->i + 1] == '>')
				|| (escap_dollar[envirment->i] == '<' && escap_dollar[envirment->i + 1] == '<')))
		{
			envirment->sub = ft_substr(escap_dollar, envirment->i, 2);
				envirment->i += 2;
		}
		else if (sign == 0 && ((check_char(escap_dollar[envirment->i])) != NULL))
		{
			envirment->sub = ft_strdup((check_char(escap_dollar[envirment->i])));
			envirment->i++;
		}
		else
			envirment->sub = copy_in_word(escap_dollar, envirment, &sign);
		if (sign == 0)
		{
			word = ft_addlist_token(ft_strdup(envirment->sub));
			ft_lstaddback_token(&token, word);
			envirment->sub = NULL;
		}
	}
	
	return (token);
}
