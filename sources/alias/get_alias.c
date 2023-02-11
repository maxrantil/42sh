/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_alias.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:58:01 by rvuorenl          #+#    #+#             */
/*   Updated: 2023/02/10 23:48:29 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

//	return everything after first word, needed to join converted first word
char	*get_post_content(char *line, char *arg)
{
	int		i;
	int		j;
	size_t	len;

	i = 0;
	j = 0;
	if (!arg || ft_strlen(arg) == 0 || ft_strequ(line, arg))
		return (ft_strdup(""));
	while (line[i] && ft_iswhitespace(line[i]))
		i++;
	while (line[i] && arg[j] && line[i] == arg[j])
	{
		i++;
		j++;
	}
	if (line[i])
	{
		len = ft_strlen(&(line[i]));
		return (ft_strsub(line, i, len));
	}
	else
		return (ft_strdup(""));
}

//	strip quotes from returned content, MALLOC
char	*get_alias_content_no_quotes(char *alias)
{
	char	*no_quotes;
	int		i;

	i = 0;
	no_quotes = get_alias_content(alias);
	while (no_quotes[i] && no_quotes[i] != '\"' && no_quotes[i] != '\'')
		i++;
	if (no_quotes[i])
		strip_quotes_single(no_quotes, i);
	return (no_quotes);
}

//	returns the command from the full 'command=content' line
char	*get_alias_command(char *alias)
{
	int	i;

	i = 0;
	while (alias[i] && alias[i] != '=')
		i++;
	if (i > 0)
		return (ft_strsub(alias, 0, i));
	else
		return (ft_strdup(""));
}

char	*get_alias_content(char *alias)
{
	int		i;
	size_t	len;
	char	*content;

	i = 0;
	while (alias[i] && (alias[i] != '='))
		i++;
	i++;			// skip '='
	len = ft_strlen(&(alias[i]));
	if (len == 0)
		content = ft_strdup("");
	else
		content = ft_strsub(alias, i, len);
	return (content);
}

int	is_command_separator(char command)
{
	if (command == '|' || command == ';' || command == '&' )
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

char	*get_first_word(char *line)
{
	int	i;
	int	j;

	// ft_printf("FW line (%s)\n", line);
	j = 0;
	while (line[j] && ft_iswhitespace(line[j]))
	{
		j++;
	}
	i = j;
	// ft_printf("FW MID i (%d) j (%d)\n", i, j);
	while (line[i] && !(ft_iswhitespace(line[i]))
		&& !(is_command_separator(line[i])))
		{
			// ft_printf("FW LOOP i (%d) j (%d)\n", i, j);
		i++;
		}
	// ft_printf("FW END i (%d) j (%d)\n", i, j);

	// if (i - j == 0)
	// 	return (NULL);
	return (ft_strsub(line, j, i - j));
}
