#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <stdio.h>
#include <readline/history.h>

// int ft_check_quotes(char c, int *sign)
// {
// 	if (c == '"' && *sign == 1)
// 		*sign = 0;
// 	else if (c == '\'' && *sign == 2)
// 		*sign = 0;
// 	else if (c == '"')
// 		*sign = 1;
// 	else if (c == '\'')
// 		*sign = 2;
// 	return (0);
// }

int	ft_countword(char const *s, char c)
{
	int	i;
	int	size;
	int sign;

	int test = 0;
	sign = 0;
	if (s == NULL)
		return (0);
	size = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c && sign == 0)
		{
			ft_check_quotes(s[i], &sign);
			i++;
		}
		if (s[i])
			size++;
		while (s[i] && (s[i] != c || s[i] == c && sign != 0))
		{
			ft_check_quotes(s[i], &sign);
			i++;
		}
	}
	return (size);
}

static void	ft_free_split(char **array, int i)
{
	while (i)
	{
		free(array[--i]);
	}
	free(array);
}

static char	*allocate_string(const char *s, int start, int end)
{
	char	*array;
	int		i;

	i = 0;
	array = (char *)malloc(sizeof(char) * (end - start + 1));
	if (array == NULL)
		return (NULL);
	while (start < end && s[start])
	{
		array[i] = s[start];
		start++;
		i++;
	}
	array[start] = 0;
	return (array);
}

static int	len_worlds(char const *s, char c)
{
	int	j;
	int sign;

	sign = 0;
	j = 0;
	while (s[j] && (s[j] != c || s[j] == c && sign != 0))
	{
		ft_check_quotes(s[j], &sign);
		j++;
	}
	return (j);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		size;
	int		i;
	int		sign;

	sign = 0;
	size = ft_countword(s, c);
	if (s == NULL || size == 0)
		return (NULL);
	array = (char **)malloc(sizeof(char *) * (size + 1));
	if (array == NULL)
		return (NULL);
	i = -1;
	while (++i < size)
	{
		while (*s && *s == c && sign == 0)
		{
			ft_check_quotes(*s, &sign);
			s++;
		}
		array[i] = allocate_string(s, 0, len_worlds(s, c));
		if (array[i] == NULL)
		{
			ft_free_split(array, i);
			return (0);
		}
		s = s + len_worlds(s, c);
	}
	array[i] = NULL;
	return (array);
}

// int main ()
// {
// 	char **commands = ft_split("aymane | 'aymane | jkhjkh' \"kjhk|lj\"", '|');
// 	int p = 0;
// 	while (commands[p])
// 	{
// 		printf("{%s}\n", commands[p]);
// 		p++;
// 	}
// }