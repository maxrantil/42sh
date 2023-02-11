/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_find_argument.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:13:39 by jakken            #+#    #+#             */
/*   Updated: 2023/02/11 16:51:24 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	operator_len(char *op)
{
	if (is_seperator(*op))
	{
		if (op[0] == '>' && ((op[1] == '>' || op[1] == '&')
				|| (op[0] == '<' && (op[1] == '<' || op[1] == '&'
						|| (op[0] == '&' && op[1] == '&')
						|| (op[0] == '|' && op[1] == '|')))))
			return (2);
		else if ((op[0] == '>' || op[0] == '<')
			&& op[1] == '&' && op[2] == '-')
			return (3);
		return (1);
	}
	return (0);
}

static char	*if_redir_or_logical(char *line, int *i, int *start, int *end)
{
	char	*ret;

	ret = NULL;
	ret = tok_if_redir(line, i, start, end);
	if (!ret)
		ret = tok_if_logical(line, i, start, end);
	return (ret);
}

static int	test_operator_error(char *line, int *end)
{
	if (*end > 0 && is_seperator(line[*end]))
	{
		if (test_if_error(&line[*end]))
		{
			*end = -1;
			return (1);
		}
	}
	return (0);
}

static void	if_redir_with_fd_go_backwards(char *line, int *end)
{
	if ((line[*end] == '>' || line[*end] == '<')
		&& *end > 0 && ft_isdigit(line[*end - 1]))
	{
		--(*end);
		while (*end > 0 && ft_isdigit(line[*end]))
			--(*end);
	}
}

char	*find_argument(char *line, int *i, int *start, int *end)
{
	char	*ret;
	char	quote;
	char	braces;

	quote = 0;
	braces = 0;
	ret = if_redir_or_logical(line, i, start, end);
	if (*end == -1)
		return (NULL);
	if (ret)
		return (ret);
	if (!is_seperator(line[*end]) || special_char_check(line, *end, '\\'))
	{
		while (line[*end] && (!is_seperator(line[*end]) || special_char_check(line, *end, '\\') || quote || braces))
			tok_quote_flag(line, end, &quote, &braces);
		if_redir_with_fd_go_backwards(line, end);
	}
	else
	{
		if (test_operator_error(line, end))
			return (NULL);
		*end += operator_len(&line[*end]);
	}
	if (*end == *start)
		++(*end);
	return (ft_strsub(line, *i, *end - *i));
}
