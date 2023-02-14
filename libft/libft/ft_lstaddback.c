/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddback.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:17:07 by mbarutel          #+#    #+#             */
/*   Updated: 2021/12/05 12:32:41 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * Ft_lstaddback() adds a new link to the end of a linked list
 * 
 * @param alst A pointer to a pointer to a linked list.
 * @param new the new element to add to the list
 */
void	ft_lstaddback(t_list **alst, t_list *new)
{
	t_list	*link;

	if (*alst)
	{
		link = *alst;
		while (link->next)
			link = link->next;
		link->next = new;
	}
	else
		*alst = new;
}
