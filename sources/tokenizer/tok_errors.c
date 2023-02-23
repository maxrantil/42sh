/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:09:10 by jniemine          #+#    #+#             */
/*   Updated: 2023/02/23 01:44:44 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	check_if_redir(char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		++i;
	while (line[i] && !is_seperator(line[i]))
		++i;
	if (line[i] == '>' || line[i] == '<')
		return (1);
	return (0);
}

static int	test_if_error_split(char *first_c, char *next_c, int err_flag)
{
	if (!err_flag && (is_seperator(*first_c)
			&& !is_semi_or_amp(*first_c)) && *next_c == '\0')
		err_flag = ft_err_print(NULL, "syntax error near unexpected token",
				"`newline'", 1);
	else if (!err_flag && ft_strnequ(first_c, "||", 1) && *(next_c + 1) == '|')
		err_flag = ft_err_print(NULL, "syntax error near unexpected token",
				"`|'", 1);
	else if (!err_flag && ft_strnequ(first_c, "||", 1)
		&& ft_strnequ(next_c + 1, "||", 2))
		err_flag = ft_err_print(NULL, "syntax error near unexpected token",
				"`|'", 1);
	else if (!err_flag && ft_strnequ(first_c, "&&", 2) && *(next_c + 1) == '&')
		err_flag = ft_err_print(NULL, "syntax error near unexpected token",
				"`&&'", 2);
	else if (!err_flag && *first_c == '&' && ft_strnequ(next_c, "&&", 2))
		err_flag = ft_err_print(NULL, "syntax error near unexpected token",
				"`&&'", 2);
	else if (!err_flag)
		return (0);
	return (1);
}

int	test_if_error(char *first_c)
{
	char	*next_c;
	int		err_flag;

	next_c = NULL;
	err_flag = 0;
	if (first_c && *first_c && !check_if_redir(first_c))
		next_c = first_c + 1;
	else
		return (0);
	if (!err_flag && *first_c == ';' && *next_c && ft_strnequ(next_c, ";;", 2))
		err_flag = ft_err_print(NULL, "syntax error near unexpected token",
				"`;;'", 2);
	else if (!err_flag && *first_c == ';' && *next_c
		&& ft_strnequ(next_c, ";", 1))
		err_flag = ft_err_print(NULL, "syntax error near unexpected token",
				"`;'", 1);
	return (test_if_error_split(first_c, next_c, err_flag));
}

static int	redir_error_split(char *str, int err_flag)
{
	if (!err_flag && *str && ft_strnequ(str, "&", 1))
		err_flag = ft_err_print(NULL, "syntax error near unexpected token",
				"`&'", 1);
	else if (!err_flag && (*str && *str == '|' && *(str + 1) != '|'))
		err_flag = ft_err_print(NULL, "syntax errorRRRR near unexpected token",
				"`|'", 1);
	else if (!err_flag && *str && ft_strnequ(str, ";;", 2))
		err_flag = ft_err_print(NULL, "syntax error near unexpected token",
				"`;;'", 2);
	else if (!err_flag && *str && ft_strnequ(str, ";", 1))
		err_flag = ft_err_print(NULL, "syntax error near unexpected token",
				"`;'", 1);
	else if (!err_flag && *str != ';' && is_seperator(*str))
	{
		*(str + 1) = '\0';
		err_flag = ft_err_print(NULL, "syntax error near unexpected token",
				str, 1);
	}
	else if (!err_flag && *str == '\0')
		err_flag = ft_err_print(NULL, "syntax error near unexpected token",
				"`newline'", 1);
	else if (!err_flag)
		return (0);
	return (1);
}

int	redir_error(char *str)
{
	int	err_flag;

	err_flag = 0;
	if (!*str)
		return (0);
	if (!err_flag && ft_strnequ(str, ">>", 2))
		err_flag = ft_err_print(NULL, "syntax error near unexpected token",
				"`>>'", 2);
	else if (!err_flag && ft_strnequ(str, "<<", 2))
		err_flag = ft_err_print(NULL, "syntax error near unexpected token",
				"`<<'", 2);
	else if (!err_flag && ft_strnequ(str, "<", 1))
		err_flag = ft_err_print(NULL, "syntax error near unexpected token",
				"`<'", 2);
	else if (!err_flag && ft_strnequ(str, ">", 1))
		err_flag = ft_err_print(NULL, "syntax error near unexpected token",
				"`>'", 1);
	return (redir_error_split(str, err_flag));
}
