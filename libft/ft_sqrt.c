/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 12:22:39 by jibot             #+#    #+#             */
/*   Updated: 2022/03/25 13:29:34 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

float	ft_sqrt(float nb)
{
	float	a;
	float	ord;

	ord = 1;
	a = 0;
	if (nb <= 0)
		return (0);
	while (a * a < nb)
		a++;
	if (a * a == nb)
		return (a);
	while (ord > 0.001)
	{
		a -= ord;
		ord *= 0.1;
		while (a * a < nb)
		{
			a += ord;
		}
	}
	return (a);
}
