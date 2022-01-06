/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 17:40:35 by jibot             #+#    #+#             */
/*   Updated: 2021/11/01 22:12:51 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	cr;
	char	*str;
	int		i;

	cr = (char)c;
	str = (char *)s;
	i = 0;
	while (s[i])
		i++;
	if (s[i] == cr)
		return (str + i);
	while (s[i - 1])
	{
		if (s[i - 1] == cr)
			return (str + i - 1);
		i--;
	}
	return (0);
}
