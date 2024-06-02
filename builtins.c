/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:28:45 by hben-laz          #+#    #+#             */
/*   Updated: 2024/06/02 18:40:24 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	l;

	l = 0;
	while (*s != '\0')
	{
		l++;
		s++;
	}
	return (l);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*ss1;
	unsigned char	*ss2;

	i = 0;
	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	while ((ss1[i] != '\0' || ss2[i] != '\0') && (n > i))
	{
		if (ss1[i] != ss2[i])
			return (ss1[i] - ss2[i]);
		i++;
	}
	if (n == i)
		return (0);
	return (ss1[i] - ss2[i]);
}

void	echo(int argc, char **argv)
{
	int	newline;
	int	indix;

	newline = 0;
	indix = 1;
	if (argc > 1 && ft_strncmp(argv[1], "-n", 2) == 0)
	{
		newline = 1;
		indix = 2;
	}
	while (indix < argc)
	{
		printf("%s", argv[indix]);
		if (indix < argc - 1)
			printf(" ");
		indix++;
	}
	if (newline != 1)
		printf("\n");
}


void	pwd()
{
	char	*s;

	s = getcwd(NULL, 0);
	if (s == NULL)
		perror("");
	printf("%s\n", s);
}
// t_env	*hello(char *name, t_env *env)
// {
	
// }
void	export(t_env **env , char *line)
{
	char	*var;
	char	*val;
	t_env	*node;
	var = get_variabl(line);
	val = get_value(line);
	node = ft_lstnew(var, val);
	ft_lstadd_back(env, node);
	
}

