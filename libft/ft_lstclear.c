/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 20:49:44 by jibot             #+#    #+#             */
/*   Updated: 2021/10/31 16:09:47 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next_lst;
	t_list	*delst;

	next_lst = *lst;
	delst = *lst;
	while (next_lst->next)
	{
		next_lst = next_lst->next;
		del (delst->content);
		free (delst);
		delst = next_lst;
	}
	del(delst->content);
	free (delst);
	*lst = NULL;
}
