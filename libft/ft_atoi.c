/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 16:17:51 by jibot             #+#    #+#             */
/*   Updated: 2021/11/02 11:56:59 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	error_check(const char *str)
{
	int	i;

	i = 0;
	if ('0' <= str[i] && str[i] <= '9')
		return (1);
	while (str[i] == 32 || (9 <= str[i] && str[i] <= 13))
		i++;
	if (str[i] != '+' && str[i] != '-' && ft_isdigit(str[i]) == 0)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!('0' <= str[i] && str[i] <= '9'))
		return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	nbr;

	if (error_check(str) == 0)
		return (0);
	i = 0;
	sign = 0;
	nbr = 0;
	while (str[i] && !('0' <= str[i] && str[i] <= '9'))
	{
		if (str[i] == '-')
			sign++;
		i++;
	}
	while (str[i] && '0' <= str[i] && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	if (sign % 2 != 0)
		nbr = -nbr;
	return (nbr);
}
