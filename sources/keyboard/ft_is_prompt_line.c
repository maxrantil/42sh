/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_prompt_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:26:34 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/29 17:13:21 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It returns a pointer to the beginning of the line if the line is a prompt
 * line, otherwise it returns NULL
 *
 * @param t the terminal structure
 * @param row the row of the cursor
 *
 * @return The address of the first character of the line.
 */
char	*ft_is_prompt_line(t_term *t, ssize_t row)
{
	if (!row || t->nl_addr[row][-1] == '\n')
		return (t->nl_addr[row]);
	return (NULL);
}
