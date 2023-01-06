/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:06:34 by mrantil           #+#    #+#             */
/*   Updated: 2022/07/13 09:27:47 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_delnode(void *content, size_t content_size)
{
	if (content != NULL)
	{
		ft_bzero(content, content_size);
		free(content);
		content = NULL;
	}
}

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*head;
	t_list	*current;

	if (!lst || !f)
		return (NULL);
	current = f(lst);
	if (!current)
		return (NULL);
	head = current;
	while (lst->next)
	{
		lst = lst->next;
		current->next = f(lst);
		if (!current->next)
		{
			ft_lstdel(&head, &ft_delnode);
			return (NULL);
		}
		current = current->next;
	}
	return (head);
}
