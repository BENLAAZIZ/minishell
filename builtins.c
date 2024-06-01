/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:53:30 by hben-laz          #+#    #+#             */
/*   Updated: 2024/06/01 12:42:34 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int newline;
	int indix;

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
        if (indix < argc - 1) {
            printf(" ");
        }
		indix++;
	}
    if (newline != 1)
        printf("\n");
}

void	cd(char **argv, char **env)
{
	// add struct f blast env
	char	*s;
  	char	*str = "ls";
	char	**cmd = ft_splith(str, ' ');
	int i = 0;
	s = getcwd(NULL, 0);
	if (s == NULL)
		perror("");
	else if (chdir(argv[2]) != 0)
	{
		puts("+++");
		printf("%s\n", s);
		while(env[i])
		{
			if (ft_strncmp(env[i], "HOME=", 5) == 0)
				break ;
			i++;
		}
		env[i] += 5;
		printf("%s", env[i]);
	}
	else
	{
		s = getcwd(NULL, 0);
		printf("curent : %s\n", s);
		execve("/bin/ls", cmd, NULL);
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