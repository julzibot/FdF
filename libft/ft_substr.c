/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 12:51:13 by jibot             #+#    #+#             */
/*   Updated: 2021/11/01 22:14:03 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	n;
	char			*tab;
	size_t			i;
	size_t			size;

	if (s == NULL)
		return (NULL);
	n = 0;
	i = ft_strlen(s);
	if (start > i)
		return (ft_strdup(""));
	else if (i - start < len)
		size = i - start;
	else
		size = len;
	tab = malloc(size + 1);
	while (n < (size_t)size)
	{
		tab[n] = s[start];
		start++;
		n++;
	}
	tab[n] = '\0';
	return (tab);
}
