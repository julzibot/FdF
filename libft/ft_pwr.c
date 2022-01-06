/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 19:41:43 by jibot             #+#    #+#             */
/*   Updated: 2021/12/08 18:48:03 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_pwr(int nb, int power)
{
	int	i;
	int	a;

	i = 1;
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	if (i < power)
	{
		a = nb;
		nb = a * (ft_pwr(nb, power - 1));
	}
	return (nb);
}
