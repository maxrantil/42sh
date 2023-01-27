/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delim_fetch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 13:35:01 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/27 20:47:29 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	delim_fetch_error(t_term *t, char *ptr)
{
	if (*ptr && ft_isseparator(*ptr))
	{
		ft_putstr_fd("\n42sh: syntax error near unexpected token `", 2);
		write(2, ptr, 1);
		ft_putstr_fd("'", 2);
	}
	else
		ft_putstr_fd("\n42sh: syntax error near unexpected token `newline'", 2);
	ft_strclr(t->inp);
	t->heredoc = 0;
}

static char	*strdelim(t_term *t)
{
	char	*ptr;
	int		delim_qty;

	ptr = t->inp;
	delim_qty = 0;
	while (*ptr)
	{
		if (*ptr == '<')
			delim_qty++;
		if (delim_qty == 2)
			return (ptr + 1);
		ptr++;
	}
	return (ptr);
}

/*
 * It fetches the delimiter
 * for a heredoc
 *
 * @param t the term structure
 */
int	ft_delim_fetch(t_term *t)
{
	char	*ptr;
	char	*end_q;

	if (t->heredoc && !t->delim)
	{
		ptr = strdelim(t);
		while (*ptr && ft_isspace(*ptr))
			ptr++;
		end_q = ptr;
		while (*end_q && !ft_isspace(*end_q) && !ft_isseparator(*end_q))
			++end_q;
		if (end_q > ptr)
			t->delim = ft_strsub(ptr, 0, (size_t)(end_q - ptr));
		else
		{
			delim_fetch_error(t, ptr);
			return (1);
		}
	}
	return (0);
}
