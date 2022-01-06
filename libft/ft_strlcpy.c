/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 15:12:59 by jibot             #+#    #+#             */
/*   Updated: 2021/11/01 22:11:24 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int		srclen;
	size_t	i;

	i = 0;
	srclen = ft_strlen(src);
	if ((int)dstsize < 0)
		dstsize = srclen + 1;
	i = 0;
	while (src[i] && i < dstsize && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize != 0)
		dst[i] = 0;
	return ((size_t)srclen);
}
