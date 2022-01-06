/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 15:01:13 by jibot             #+#    #+#             */
/*   Updated: 2021/11/01 22:11:10 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	int		dstlen;
	size_t	i;
	size_t	n;
	size_t	maxlen;

	dstlen = ft_strlen((const char *)dst);
	maxlen = ft_strlen(src);
	if (dstsize > (size_t)dstlen)
	{
		i = (size_t)dstlen;
		n = 0;
		while (src[n] && n < dstsize - (size_t)dstlen - 1)
		{
			dst[i] = src[n];
			n++;
			i++;
		}
		dst[i] = '\0';
	}
	else
		return (maxlen + dstsize);
	return (maxlen + dstlen);
}
