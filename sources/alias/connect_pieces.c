/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_pieces.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:38:32 by rvuorenl          #+#    #+#             */
/*   Updated: 2023/02/15 16:38:59 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static size_t	total_line_len(char *pre, char *conv, char *post, char **new)
{
	size_t	tot_len;

	tot_len = 0;
	if (pre)
		tot_len += ft_strlen(pre);
	if (conv)
		tot_len += ft_strlen(conv);
	if (post)
		tot_len += ft_strlen(post);
	if (tot_len > 0)
		*new = ft_strnew(tot_len);
	return (tot_len);
}

static void	free_parsed_line(char **pre, char **conv, char **post, char **new)
{
	if (pre && *pre)
		ft_strdel(pre);
	if (conv && *conv)
		ft_strdel(conv);
	if (post && *post)
		ft_strdel(post);
	if (new && *new)
		ft_strdel(new);
}

void	connect_alias_pieces(char **pre, char **conv, char **post, char **line)
{
	char	*new_line;

	if (total_line_len(*pre, *conv, *post, &new_line))
	{
		ft_strdel(line);
		if (*pre)
		{
			ft_strcpy(new_line, *pre);
			if (*conv)
				ft_strcat(new_line, *conv);
			if (*post)
				ft_strcat(new_line, *post);
		}
		else if (*conv)
		{
			ft_strcpy(new_line, *conv);
			if (*post)
				ft_strcat(new_line, *post);
		}
		else
			ft_strcpy(new_line, *post);
		*line = ft_strdup(new_line);
		free_parsed_line(pre, conv, post, &new_line);
	}
}
