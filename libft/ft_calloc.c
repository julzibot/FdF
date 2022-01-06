/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 16:39:39 by jibot             #+#    #+#             */
/*   Updated: 2021/11/01 21:49:13 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*tab;
	size_t	i;

	tab = malloc(size * count);
	i = 0;
	while (i < size * count)
	{
		tab[i] = '\0';
		i++;
	}
	return (tab);
}
