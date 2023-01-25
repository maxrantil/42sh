/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:18:03 by mbarutel          #+#    #+#             */
/*   Updated: 2021/12/09 10:51:02 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * It creates a new list element, and if the content and content_size are not 
 * NULL, it allocates memory for the content, copies the content into the new 
 * element, and sets the content_size
 * 
 * @param content the content of the new list element
 * @param content_size The size of the content of the new list element.
 * 
 * @return A pointer to a new list element.
 */
t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		ft_exit_no_mem(1);
	if (content && content_size)
	{
		new->content = ft_memalloc(content_size);
		if (!new->content)
		{
			ft_lstdelone(&new, ft_del);
			return (NULL);
		}
		new->content = ft_memcpy(new->content, content, content_size);
		new->content_size = content_size;
	}
	else
	{
		new->content = NULL;
		new->content_size = 0;
	}
	new->next = NULL;
	return (new);
}
