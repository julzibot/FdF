/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 19:34:52 by jibot             #+#    #+#             */
/*   Updated: 2021/11/02 12:00:13 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	is_set(char c, char const *set)
{
	int	i;

	i = 0;
	if (ft_strncmp(set, "", 1) == 1)
		return (0);
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		n;
	char	*tab;

	i = 0;
	n = 0;
	if (s1 == NULL || !(*s1))
		return (ft_strdup(""));
	while (is_set(s1[i], set) == 1)
		i++;
	j = ft_strlen(s1);
	while (i != j && is_set(s1[j - 1], set) == 1)
		j--;
	tab = malloc(j - i + 1);
	while (s1[i] && i < j)
	{
		tab[n] = s1[i];
		n++;
		i++;
	}
	tab[n] = '\0';
	return (tab);
}
