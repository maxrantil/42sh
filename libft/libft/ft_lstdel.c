/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:17:22 by mbarutel          #+#    #+#             */
/*   Updated: 2021/12/07 17:39:36 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * It deletes a list.
 * 
 * @param alst A pointer to the first link of a list.
 * @param del pointer to a function that takes two parameters, the first being
 * a pointer to the memory that needs to be freed, and the second being the size
 * of the memory that needs to be freed.
 */
void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*ptr;

	if (alst)
	{
		while (*alst)
		{
			ptr = (*alst)->next;
			ft_lstdelone(alst, del);
			(*alst) = ptr;
		}
		ptr = NULL;
	}
}
