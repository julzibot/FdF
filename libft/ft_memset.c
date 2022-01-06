/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 16:23:33 by jibot             #+#    #+#             */
/*   Updated: 2021/11/01 22:06:23 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	n;
	unsigned char	*s;

	i = 0;
	s = (unsigned char *)b;
	n = (unsigned char)c;
	while (i < len)
	{
		s[i] = c;
		i++;
	}
	return (s);
}
