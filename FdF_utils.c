/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 21:48:09 by jibot             #+#    #+#             */
/*   Updated: 2022/01/13 22:02:42 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

float	ft_min(float a, float b)
{
	if (a <= b)
		return (a);
	return (b);
}

float	ft_max(float a, float b)
{
	if (a >= b)
		return (a);
	return (b);
}

int	ft_tablen(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	**ft_tabdup(char **data)
{
	int		i;
	char	**dup;

	i = 0;
	while (data[i])
		i++;
	dup = malloc(sizeof(char *) * i + 1);
	i = 0;
	while (data[i])
	{
		dup[i] = data[i];
		i++;
	}
	dup[i] = NULL;
	free(data);
	return (dup);
}
