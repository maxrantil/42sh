/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:17:54 by mbarutel          #+#    #+#             */
/*   Updated: 2021/12/09 09:33:09 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * It takes a list and a function as parameters. It applies the function to 
 * each element of the list and creates a new list with the results.
 * 
 * @param lst a pointer to the first element of a linked list
 * @param f a function that takes a t_list pointer and returns a t_list pointer
 * 
 * @return A pointer to a new list.
 */
t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*newlist;

	if (lst && f)
	{
		newlist = f(lst);
		if (!newlist)
		{
			ft_lstdel(&newlist, ft_del);
			return (NULL);
		}
		if (newlist && lst->next)
			newlist->next = ft_lstmap(lst->next, f);
		return (newlist);
	}
	return (NULL);
}
