/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_h.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 09:56:23 by hben-laz          #+#    #+#             */
/*   Updated: 2024/07/24 12:02:55 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*tab;

	i = 0;
	if (s2 == NULL)
		return (ft_strdup(s1));
	if (s1 == NULL)
		return (ft_strdup(s2));
	tab = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (tab == NULL)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		tab[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < ft_strlen(s2))
		tab[i++] = s2[j++];
	tab[i] = '\0';
	return (tab);
}
