/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delim_fetch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 13:35:01 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/24 00:01:12 by mbarutel         ###   ########.fr       */
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

static void	bslash_on(t_term *t, char *ptr)
{
	char *end_q;

	while (*ptr && ft_isspace(*ptr))
		ptr++;
	end_q = ptr;
	while (*end_q && !ft_isspace(*end_q) && !ft_isseparator(*end_q))
		++end_q;
	if (end_q > ptr)
		t->delim = ft_strsub(ptr, 0, (size_t)(end_q - ptr));
	else
		delim_fetch_error(t, ptr);
}

static void bslash_off(t_term *t, char *ptr)
{
	int	i;
	
	i = -1;
	t->delim = ft_strdup(ptr);
	ft_printf("delim: [%s]\n", t->delim);
	while (t->delim[++i])
	{
		if ((t->delim[i] == '\\' && special_char_check(t->delim, i, '\\')) || t->delim[i] == '\n')
		{
			ft_memmove((void *)&t->delim[i], (void *)&t->delim[i + 1], \
			ft_strlen(&t->delim[i + 1]) + 1);
		}	
		if (t->delim[i + 1] && t->delim[i + 1] != '\\' && !special_char_check(t->delim, i + 1, '\\'))
		{
			ft_strclr(&t->delim[i + 1]);
			break ;
		}
	}	
	ft_printf("delim: [%s]\n", t->delim);
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
	char 	*end_q;

	if (t->heredoc && !t->delim)
	{
		ptr = strdelim(t);
		end_q = ptr;
		while (*end_q && ft_isspace(*end_q) && *end_q != '\\')
			end_q++;
		if (*end_q == '\\')
			bslash_on(t, ptr);
		else
			bslash_off(t, ptr);
	}
	return (0);
}
