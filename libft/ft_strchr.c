/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 17:34:51 by jibot             #+#    #+#             */
/*   Updated: 2021/11/01 22:09:51 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	cr;
	char	*str;
	int		i;

	cr = (char)c;
	str = (char *)s;
	i = 0;
	while (s[i])
	{
		if (s[i] == cr)
			return (str + i);
		i++;
	}
	if (s[i] == cr)
		return (str + i);
	return (0);
}
