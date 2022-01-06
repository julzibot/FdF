/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 13:01:55 by jibot             #+#    #+#             */
/*   Updated: 2021/11/16 20:37:40 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	char	*tab;

	if (!s || !f)
		return (NULL);
	len = 0;
	while (s[len])
		len++;
	tab = malloc(len + 1);
	if (tab == NULL)
		return (NULL);
	len = 0;
	while (s[len])
	{
		tab[len] = f(len, s[len]);
		len++;
	}
	tab[len] = '\0';
	return (tab);
}
