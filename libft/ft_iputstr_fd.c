/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 17:14:40 by jibot             #+#    #+#             */
/*   Updated: 2021/12/08 19:06:54 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_iputstr_fd(char *s, int fd)
{
	unsigned int	i;
	int				count;

	i = 0;
	count = 0;
	if (s == NULL)
		return (ft_iputstr_fd("(null)", 1));
	while (s[i])
	{
		count += ft_iputchar_fd(s[i], fd);
		i++;
	}
	return (count);
}
