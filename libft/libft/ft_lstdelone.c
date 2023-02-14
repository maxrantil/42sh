/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:17:29 by mbarutel          #+#    #+#             */
/*   Updated: 2021/12/09 10:52:12 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * This function takes a pointer to a pointer to a linked list and a pointer 
 * to a function that takes a pointer to a void and a size_t as arguments. It 
 * frees the memory of the linked list pointed to by the pointer to a pointer 
 * to a linked list and sets the pointer to a pointer to a linked list to NULL
 * 
 * @param alst A pointer to a pointer to a linked list.
 * @param del a function that takes two parameters, the first being a pointer 
 * to the content of the node, and the second being the size of the content.
 */
void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	if (alst)
	{
		del((*alst)->content, (*alst)->content_size);
		free(*alst);
		(*alst) = NULL;
	}
}
