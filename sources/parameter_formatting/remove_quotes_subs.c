/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes_subs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 21:46:00 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/23 22:06:14 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	see_quote(t_subquo *sub, char *str)
{
	if ((*str && str[sub->i] == '\'') || (*str && str[sub->i] == '"'))
	{
		while (str[sub->i] == '"' && sub->s_quote == 0)
		{
			sub->d_quote += 1;
			sub->i += 1;
		}
		while (str[sub->i] == '\'' && sub->d_quote == 0)
		{
			sub->s_quote += 1;
			sub->i += 1;
		}
		if (sub->s_quote >= 2 || sub->d_quote >= 2)
			return (1);
	}
	return (0);
}

static void	init_subquo(t_subquo *sub, char *str)
{
	sub->d_quote = 0;
	sub->s_quote = 0;
	sub->i = 0;
	sub->k = 0;
	sub->closed = 0;
	sub->new = ft_strnew(ft_strlen(str));
}

char	*remove_quotes_subs(char **str)
{
	t_subquo	sub;

	init_subquo(&sub, *str);
	while ((*str)[sub.i])
	{
		sub.closed = see_quote(&sub, *str);
		if (sub.closed)
		{
			sub.d_quote = 0;
			sub.s_quote = 0;
		}
		if (!(*str)[sub.i])
			break ;
		sub.new[sub.k++] = (*str)[sub.i++];
	}
	ft_strdel(str);
	return (sub.new);
}
