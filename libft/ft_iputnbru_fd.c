/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbru_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:30:31 by jibot             #+#    #+#             */
/*   Updated: 2021/12/08 19:06:43 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_iputnbru_fd(unsigned int n, int fd)
{
	unsigned int	mod;
	int				count;
	char			c;

	count = 0;
	if (n >= 10)
	{
		mod = (n % 10);
		n /= 10;
		c = mod + '0';
		count += ft_iputnbru_fd(n, fd);
		count += ft_iputchar_fd(c, fd);
	}
	else
	{
		c = n + '0';
		count += ft_iputchar_fd(c, fd);
	}
	return (count);
}
