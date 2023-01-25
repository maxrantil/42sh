/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_term_val.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:39:35 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/12 13:19:35 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

extern t_term	*g_t;

/*
 * It gets the current line number of the cursor
 *
 * @return The line number of the cursor.
 */

void	get_term_val(ssize_t *term_val)
{
	char	buf[32];
	int		len;

	ft_memset(buf, '\0', sizeof(buf));
	write(0, "\033[6n", 4);
	read(0, buf, 32);
	len = ft_strlen(buf);
	while (len && buf[len] != ';')
		len--;
	term_val[0] = ft_atoi(buf + len + 1) - 1;
	term_val[1] = ft_atoi(buf + 2) - 1;
}
