/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_bslash_removal.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:38:31 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/17 13:59:07 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static bool	blash_check(char *buff, int pos)
{
	int		count;

	if (pos < 0)
		return (false);
	count = 0;
	while (pos >= 0 && buff[pos] == '\\')
	{
		count++;
		pos--;
	}
	if (count % 2)
		return (true);
	return (false);
}

static void	ft_qoute_parse(char *buff, char *quote, int len)
{
	if (!len || buff[len - 1] != '\\' || !blash_check(buff, len - 1))
	{
		if (!(*quote))
			*quote = buff[len];
		else if (*quote == buff[len])
			*quote = 0;
		if (!(*quote) || *quote == buff[len])
		{
			ft_memmove((void *)&buff[len], (void *)&buff[len + 1], \
			ft_strlen(&buff[len + 1]) + 1);
		}
	}
}

static void	ft_blash_parse(char *buff, char *quote, int len)
{
	// if (*quote == S_QUO && !blash_check(buff, len))
	// {
	// 	ft_memmove((void *)&buff[len], (void *)&buff[len + 1],
	// 	ft_strlen(&buff[len + 1]) + 1);
	// }
	if (*quote == D_QUO && !blash_check(buff, len))
	{
		ft_memmove((void *)&buff[len], (void *)&buff[len + 1], \
			ft_strlen(&buff[len + 1]) + 1);
	}
	else if (!*quote && blash_check(buff, len))
	{
		ft_memmove((void *)&buff[len], (void *)&buff[len + 1], \
			ft_strlen(&buff[len + 1]) + 1);
	}
}

static void	handle_newline(char *buff, int len)
{
	ft_memmove((void *)&buff[len], (void *)&buff[len + 1], \
	ft_strlen(&buff[len + 1]) + 1);
	if (len && buff[len - 1] == '\\')
	{
		len--;
		ft_memmove((void *)&buff[len], (void *)&buff[len + 1], \
		ft_strlen(&buff[len + 1]) + 1);
	}
}

void	ft_quote_blash_removal(char *buff)
{
	int		len;
	char	quote;

	quote = 0;
	len = ft_strlen(buff);
	while (--len >= 0)
	{
		if (buff[len] == '\\')
			ft_blash_parse(buff, &quote, len);
		else if (buff[len] == '\n' && len && blash_check(buff, len - 1))
			handle_newline(buff, len);
		else if ((buff[len] == S_QUO || buff[len] == D_QUO))
			ft_qoute_parse(buff, &quote, len);
	}
}
