/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:28:45 by hben-laz          #+#    #+#             */
/*   Updated: 2024/06/01 22:36:45 by hben-laz         ###   ########.fr       */
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

void	cd(char **argv, t_env **envv)
{
	char	*s;
	t_env *current;
	
	current = *envv;
	s = getcwd(NULL, 0);
	if (s == NULL)
		perror("");
	else if (chdir(argv[2]) != 0)
	{
		while(current)
		{
			if ((ft_strncmp(current->variable, "HOME", 4) == 0) &&
				 (ft_strlen(current->variable) == ft_strlen("HOME")))
				break ;
			current = current->next;
		}
		printf("%s", current->value);
	}
	else
	{
		s = getcwd(NULL, 0);
		printf("curent : %s\n", s);
	}
}

void	pwd()
{
	char	*s;

	s = getcwd(NULL, 0);
	if (s == NULL)
		perror("");
	printf("%s\n", s);
}
// t_env	*hello(char *name, t_env *envv)
// {
	
// }

void	export(t_env **envv , char *line)
{
	char	*var;
	char	*val;
	t_env	*node;
	// int		i;

	// i = 0;
	// if (line[0] == '+' || (line[0] >= '0' && line[i] <= '9'))
	// while (line[i])
	// {
	// }
	var = get_variabl(line);
	val = get_value(line);
	node = ft_lstnew(var, val);
	ft_lstadd_back(envv, node);
	
}
