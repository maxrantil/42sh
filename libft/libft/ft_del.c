/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 11:09:00 by mbarutel          #+#    #+#             */
/*   Updated: 2021/12/13 23:05:06 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * It frees the content of a link and sets the content_size to 0
 * 
 * @param content The content of the node to be deleted.
 * @param content_size The size of the content of the node.
 */
void	ft_del(void *content, size_t content_size)
{
	free(content);
	(void) content_size;
}
