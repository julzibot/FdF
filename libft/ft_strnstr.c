/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 15:20:48 by jibot             #+#    #+#             */
/*   Updated: 2021/11/01 22:12:34 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	n;
	size_t	icount;

	i = 0;
	icount = 0;
	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		n = 0;
		while (i > icount)
			i--;
		while (haystack[i] && haystack[i] != needle[n] && i < len)
			i++;
		while (haystack[i] && haystack[i] == needle[n] && i < len)
		{
			i++;
			n++;
		}
		if (needle[n] == '\0')
			return ((char *)haystack + i - n);
		icount++;
	}
	return (NULL);
}
