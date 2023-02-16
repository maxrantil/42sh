/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_add_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 21:48:14 by rvuorenl          #+#    #+#             */
/*   Updated: 2023/02/16 12:23:35 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	have_single_quotes(char *content)
{
	size_t	len;

	if (content)
		len = ft_strlen(content);
	else
		return (0);
	if (len > 0)
	{
		if (content[0] == '\'' && content[len - 1] == '\'')
			return (1);
	}
	return (0);
}

static int	skip_single_quotes(char *str, int i)
{
	while (str[i] && str[i] != '\'')
		i++;
	if (!str[i])
		return (i - 1);
	return (i);
}

static void	rm_double_quotes(char *str)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(str);
	while (str[i])
	{
		if (str[i] == '\"')
		{
			if (!(str[i + 1]))
				ft_memmove(&str[i], &str[i + 1], 1);
			else
				ft_memmove(&str[i], &str[i + 1], len - i);
			len--;
			str[len] = '\0';
			i--;
		}
		else if (str[i] == '\'')
		{
			i = skip_single_quotes(str, i);
		}
		i++;
	}
}

void	add_quotes(char **content)
{
	char	*added_quotes;
	char	*tmp;

	if (!validate_whitespace(*content))
		tmp = ft_strtrim(*content);
	else
		tmp = ft_strdup(*content);
	if (have_single_quotes(tmp))
	{
		ft_strdel(content);
		*content = ft_strdup(tmp);
		ft_strdel(&tmp);
		return ;
	}
	if (tmp)
	{
		rm_double_quotes(tmp);
		added_quotes = ft_strjoin_three("\'", tmp, "\'");
		ft_strdel(&tmp);
	}
	else
		added_quotes = ft_strdup("''");
	ft_strdel(content);
	*content = ft_strdup(added_quotes);
	ft_strdel(&added_quotes);
}
