/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:09:10 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/24 10:59:42 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
//Saved if needed
int	control_op_error(char *str)
{
	if (*str == '|' && ft_strnequ(str + 1, "||", 2))
		ft_err_print(NULL, "syntax error near unexpected token",
			"`||'", 2);
	else if (*str == '|' && ft_strnequ(str + 1, "|", 1))
		ft_err_print(NULL, "syntax error near unexpected token",
			"`|'", 1);
	else if (*str == '&' && ft_strnequ(str + 1, "&&", 2))
		ft_err_print(NULL, "syntax error near unexpected token",
			"`&&'", 2);
	else if (*str == '&' && ft_strnequ(str + 1, "&", 1))
		ft_err_print(NULL, "syntax error near unexpected token",
			"`&'", 1);
	else if (*str == ';' && ft_strnequ(str + 1, ";;", 2))
		ft_err_print(NULL, "syntax error near unexpected token",
			"`;;'", 2);
	return (control_op_error_split(str));
}
*/

static int	test_if_error_split(char *line, char *str, int err_flag)
{
	if (!err_flag && (is_seperator(*line) && !is_semi_or_amp(*line)) && *str == '\0')
		err_flag = ft_err_print(NULL, "syntax error near unexpected token",
				"`newline'", 1);
	else if (!err_flag && is_seperator(*line) && *str && is_seperator(*str))
	{
		*(str + 1) = '\0';
		err_flag = ft_err_print(NULL, "syntax error near unexpected token",
				str, 1);
	}
	else if (!err_flag)
		return (0);
	return (1);
}

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

int	test_if_error(char *line)
{
	char	*str;
	int		err_flag;

	str = NULL;
	err_flag = 0;
	if (line && *line && !check_if_redir(line))
		str = line + 1;
	else
		return (0);
	if (!err_flag && *line == '|' && (*str && *str == '|'))
		err_flag = ft_err_print(NULL, "syntax error near unexpected token",
				"`|'", 1);
	else if (!err_flag && *line == ';' && *str && ft_strnequ(str, ";;", 2))
		err_flag = ft_err_print(NULL, "syntax error near unexpected token",
				"`;;'", 2);
	else if (!err_flag && *line == ';' && *str && ft_strnequ(str, ";", 1))
		err_flag = ft_err_print(NULL, "syntax error near unexpected token",
				"`;'", 1);
	return (test_if_error_split(line, str, err_flag));
}

static int	redir_error_split(char *str, int err_flag)
{
	if (!err_flag && ft_strnequ(str, "&", 1))
		err_flag = ft_err_print(NULL, "syntax error near unexpected token",
				"`&'", 1);
	else if (!err_flag && (*str && *str == '|'))
		err_flag = ft_err_print(NULL, "syntax error near unexpected token",
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
