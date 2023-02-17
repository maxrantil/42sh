/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_expansion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:09:48 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/17 13:15:58 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	expand(t_term *t, int i, int pos, int len)
{
	char	*begin;
	char	*end;
	char	*ret;
	int		cpy_len;

	begin = ft_strsub(t->inp, 0, i);
	end = ft_strdup(t->inp + i + len);
	ret = ft_strjoin_three(begin, t->history_arr[t->history_size - pos], end);
	ft_strdel(&begin);
	ft_strdel(&end);
	if (!ret)
		return (0);
	ft_strclr(t->inp);
	cpy_len = ft_strlen(ret);
	t->bytes = -1;
	while (++t->bytes < cpy_len && t->bytes < BUFF_SIZE - 1)
		t->inp[t->bytes] = ret[t->bytes];
	ft_strdel(&ret);
	return (1);
}

static int	expand_specific(t_term *t, int i, int prefix)
{
	int		j;
	int		int_len;
	int		digit;

	j = i + prefix;
	int_len = 1;
	while (t->inp[j] == '0' && ++j)
		int_len++;
	digit = t->inp[j++] - 48;
	while (ft_isdigit(t->inp[j]))
	{
		digit *= 10;
		digit += t->inp[j++] - 48;
		int_len++;
		if (digit > (int)t->history_size)
			break ;
	}
	if (prefix == 1 && digit < (int)t->history_size)
		digit = t->history_size - digit + 1;
	if (digit > (int)t->history_size)
		return (ft_history_print_error(t->inp + i + prefix, prefix));
	return (expand(t, i, digit, int_len + prefix));
}

static int	find_matching(t_term *t, char *str, int i)
{
	int		y;
	int		x;
	int		len;

	y = t->history_size - 1;
	len = ft_strlen(str);
	while (y > 0)
	{
		x = 0;
		while (t->history_arr[y][x] && str[x] && t->history_arr[y][x] == str[x])
			x++;
		if (x == len)
		{
			expand(t, i, t->history_size - y, len + 1);
			break ;
		}
		y--;
	}
	if (y == 0)
		return (ft_history_print_error(str, 0));
	ft_strdel(&str);
	return (1);
}

static int	expand_last_match(t_term *t, int i, int init)
{
	char	*str;
	int		j;

	j = i + init;
	while (!ft_isspace(t->inp[j]))
		j++;
	str = ft_strnew(j);
	j = i + init;
	while (!ft_isspace(t->inp[j]))
	{
		str[j - i - init] = t->inp[j];
		j++;
	}
	return (find_matching(t, str, i));
}

int	ft_history_expantion(t_term *t)
{
	int		i;
	int		status;

	status = -1;
	i = -1;
	while (t->inp[++i])
	{
		if (t->inp[0] && t->inp[1] && t->inp[i] == '!')
		{
			if (t->inp[i] == '!' && t->inp[i + 1] == '!' && t->history_size)
				status = expand(t, i, 1, 2);
			else if (t->inp[i] == '!' && ft_isalpha(t->inp[i + 1]))
				status = expand_last_match(t, i, 1);
			else if (t->inp[i] == '!' && ft_isdigit(t->inp[i + 1]))
				status = expand_specific(t, i, 1);
			else if (t->inp[2] && t->inp[i] == '!' \
				&& t->inp[i + 1] == '-' && ft_isdigit(t->inp[i + 2]))
				status = expand_specific(t, i, 2);
		}
	}
	if (status > 0)
	{
		ft_printf("\n%s", t->inp);
		++t->total_row;
	}
	return (status);
}
