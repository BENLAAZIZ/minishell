#include "minishell.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*copy;
	size_t	j;
	if (s1 == NULL)
		return (NULL);
	i = ft_strlen(s1);
	copy = (char *)malloc(i + 1);
	if (copy == NULL)
		return (NULL);
	j = 0;
	while (j < i)
	{
		copy[j] = s1[j];
		j++;
	}
	copy[j] = '\0';
	return (copy);
}