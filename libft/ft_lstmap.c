/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 16:14:15 by jibot             #+#    #+#             */
/*   Updated: 2021/11/01 21:26:06 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*flist;
	t_list	*temp;

	flist = NULL;
	if (!lst || ft_lstsize(lst) == 0 || !f || !del)
		return (NULL);
	while (lst != NULL)
	{
		temp = ft_lstnew(f(lst->content));
		ft_lstadd_back(&flist, temp);
		if (lst->next)
			lst = lst->next;
		else
			return (flist);
	}
	return (flist);
}
