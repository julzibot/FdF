/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 17:48:45 by jibot             #+#    #+#             */
/*   Updated: 2021/11/01 22:05:16 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	cr;
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *)s;
	cr = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (str[i] == cr)
			return (str + i);
		i++;
	}
	return (0);
}
