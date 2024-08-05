/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:34:45 by hben-laz          #+#    #+#             */
/*   Updated: 2024/08/05 18:29:20 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_word(const char *s, char c)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && s[i] != '\t')
		{
			len++;
			while ((s[i] != c && s[i] != '\t') && s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (len);
}

static char	*charge_word(const char *s, int start, int end)
{
	int		i;
	int		size;
	char	*ptr;

	i = 0;
	size = (end - start);
	ptr = (char *)malloc(sizeof(char) * (size + 1));
	if (ptr == NULL)
		return (NULL);
	while (i < size)
	{
		ptr[i] = s[start];
		i++;
		start++;
	}
	ptr[i] = '\0';
	return (ptr);
}

static void	free_function(char **array, int i)
{
	i--;
	while (i >= 0)
	{
		free(array[i]);
		i--;
	}
	free(array);
}

static char	**my_array(char **array, char const *s, char c, int nbr_word)
{
	int		i;
	int		j;
	int		end;

	i = -1;
	j = 0;
	while (++i < nbr_word)
	{
		while ((s[j] == c || s[j] == '\t') && s[j] != '\0')
			j++;
		end = j;
		while ((s[end] != c && s[end] != '\t') && s[end] != '\0')
			end++;
		array[i] = charge_word(s, j, end);
		if (array[i] == NULL)
		{
			free_function(array, i);
			return (0);
		}
		j = end;
	}
	array[i] = NULL;
	return (array);
}

char	**ft_splith(char const *s, char c)
{
	char	**array;
	int		nbr_wrd;

	if (s == NULL)
		return (NULL);
	nbr_wrd = count_word(s, c);
	if (nbr_wrd == 0)
		return (NULL);
	array = (char **)malloc(sizeof(char *) * (nbr_wrd + 1));
	if (array == NULL)
		return (NULL);
	return (my_array(array, s, c, nbr_wrd));
}
