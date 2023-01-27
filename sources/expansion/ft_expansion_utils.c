/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:38:31 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/27 13:19:17 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	ft_qoute_parse(char *buff, char *quote, int len)
{
	if (!len || buff[len - 1] != '\\' || !special_char_check(buff, len, '\\'))
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
	if (!(*quote) && special_char_check(buff, len + 1, '\\'))
	{
		ft_memmove((void *)&buff[len], (void *)&buff[len + 1], \
		ft_strlen(&buff[len + 1]) + 1);
	}
	else if (*quote == D_QUO && !special_char_check(buff, len + 1, '\\'))
		ft_memmove((void *)&buff[len], (void *)&buff[len + 1], \
			ft_strlen(&buff[len + 1]) + 1);
}

void	ft_quote_blash_removal(char *buff)
{
	int		len;
	char	quote;

	quote = 0;
	len = ft_strlen(buff);
	while (len >= 0)
	{
		if ((buff[len] == S_QUO || buff[len] == D_QUO))
			ft_qoute_parse(buff, &quote, len);
		else if (buff[len] == '\\')
			ft_blash_parse(buff, &quote, len);
		else if (buff[len] == '\n' && len && special_char_check(buff, len, '\\'))
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
		len--;
	}
}
