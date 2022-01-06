/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:04:11 by jibot             #+#    #+#             */
/*   Updated: 2021/12/08 19:07:46 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_puthexp(unsigned long n, char c)
{
	char				*base;
	static int			count;
	unsigned long		mod;

	count = 2;
	if (c == 'x')
		base = "0123456789abcdef";
	else if (c == 'X')
		base = "0123456789ABCDEF";
	if (n >= 16)
	{
		mod = n % 16;
		n /= 16;
		ft_puthexp(n, c);
		count += ft_iputchar_fd(base[mod], 1);
	}
	else
		count += ft_iputchar_fd(base[n], 1);
	return (count);
}
