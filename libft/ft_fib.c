/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fibonacci.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 20:26:07 by jibot             #+#    #+#             */
/*   Updated: 2021/12/08 18:43:35 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_fib(int index)
{
	int	nb;

	if (index < 0)
		return (-1);
	if (index <= 1)
		return (index);
	else
		nb = (ft_fib(index - 2) + ft_fib(index - 1));
	return (nb);
}