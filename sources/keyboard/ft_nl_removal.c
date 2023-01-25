/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nl_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:00:30 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/04 17:27:28 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * It removes the newline character from the history buffer if it's preceded 
 * by a backslash or if it's the last character in the buffer
 * 
 * @param t the term structure
 */
int	ft_nl_removal_bslash_check(t_term *t, ssize_t pos)
{
	ssize_t	start;
	ssize_t	count;

	start = pos - 1;
	while (start && t->history_buff[start] == '\\')
		start--;
	if (start)
		start++;
	count = start;
	while (count < t->bytes && t->history_buff[count] == '\\')
		count++;
	if ((count - start) % 2)
		return (1);
	return (0);
}

/**
 * It takes a string, and if it finds a backslash, it replaces it with a
 * semicolon and a space
 * 
 * @param t the term structure
 * @param i the current position in the history buffer
 * 
 * @return The position of the last backslash.
 */
static int	ft_get_bslash_pos(t_term *t, int i)
{
	int	count;

	count = i - 1;
	while (count && t->history_buff[count] == '\\')
		count--;
	if (count)
		count++;
	if ((i - count) > 1)
	{
		t->history_buff[i++] = ';';
		ft_memmove((void *)&t->history_buff[i + 1], \
		(void *)&t->history_buff[i], ft_strlen(&t->history_buff[i]) + 1);
		t->history_buff[i] = ' ';
		return (i);
	}
	else
		return (i - 1);
}

void	ft_nl_removal(t_term *t)
{
	int		k;
	int		i;
	char	quote;

	k = -1;
	quote = 0;
	while (t->history_buff[++k])
	{
		i = k;
		if (!quote && t->history_buff[i] == '\n' \
		&& ft_nl_removal_bslash_check(t, i))
			k = ft_get_bslash_pos(t, i++);
		else if ((t->history_buff[i] == S_QUO || t->history_buff[i] == D_QUO) \
		&& !ft_nl_removal_bslash_check(t, i))
		{
			if (!quote)
				quote = t->history_buff[i];
			else if (quote == t->history_buff[i])
				quote = 0;
		}
		ft_memmove((void *)&t->history_buff[k], (void *)&t->history_buff[i], \
		ft_strlen(&t->history_buff[i]) + 1);
	}
	if (t->delim)
		ft_strclr(ft_strchr(t->history_buff, '\n'));
}
