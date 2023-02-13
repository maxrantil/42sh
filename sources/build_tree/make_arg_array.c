/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_arg_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 21:59:23 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/13 17:42:36 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"
// static void	quote_brace_check(char *qoute, char *brace, int *brace_count, \
// char *cmd)
// {
// 	if (*cmd == S_QUO || *cmd == D_QUO)
// 	{
// 		if (!*qoute)
// 			*qoute = *cmd;
// 		else if (*qoute == *cmd)
// 			*qoute = 0;
// 	}
// 	if (*cmd == L_BRAC || *cmd == R_BRAC)
// 	{
// 		if (!*brace || *brace == *cmd)
// 		{
// 			++(*brace_count);
// 			*brace = *cmd;
// 		}
// 		else if (*brace != *cmd)
// 		{
// 			if (*brace_count)
// 				--(*brace_count);
// 			else
// 				*brace = 0;
// 		}
// 	}
// }

// void	tok_quote_flag(char *line, int *end, t_token_flags *flags)
// {
// 	if (line[*end] == S_QUO || (line[*end] == D_QUO \
// 	&& (!*end || !special_char_check(line, *end, '\\'))))
// 	{
// 		if (!flags->quote)
// 			flags->quote = line[*end];
// 		else if (flags->quote == line[*end])
// 			flags->quote = 0;
// 	}
// 	else if ((line[*end] == L_BRAC \
// 	&& (!*end || special_char_check(line, *end, '$'))) || line[*end] == R_BRAC)
// 	{
// 		if (!flags->braces || flags->braces == line[*end])
// 		{
// 			flags->braces = line[*end];
// 			++flags->braces_count;
// 		}
// 		else if (flags->braces != line[*end])
// 		{
// 			--flags->braces_count;
// 			if (!flags->braces_count)
// 				flags->braces = 0;
// 		}
// 	}
// 	++(*end);
// }

static void	quote_brace_check(char *cmd, int pos, t_token_flags *flags)
{
	if (cmd[pos] == S_QUO || (cmd[pos] == D_QUO \
	&& (!pos || !special_char_check(cmd, pos, '\\'))))
	{
		if (!flags->quote)
			flags->quote = cmd[pos];
		else if (flags->quote == cmd[pos])
			flags->quote = 0;
	}
	else if ((cmd[pos] == L_BRAC && (!pos || special_char_check(cmd, pos, '$'))) || cmd[pos] == R_BRAC)
	{
		if (!flags->braces || flags->braces == cmd[pos])
		{
			flags->braces = cmd[pos];
			++flags->braces_count;
		}
		else if (flags->braces != cmd[pos])
		{
			--flags->braces_count;
			if (!flags->braces_count)
				flags->braces = 0;
		}
	}
}

static int	arg_qty_loop(char *cmd, t_token_flags *flags)
{
	int				pos;
	int				len;
	
	pos = 0;
	len = 0;
	while (cmd[pos])
	{
		len++;
		while (cmd[pos])
		{
			quote_brace_check(cmd, pos, flags);
			if (ft_isspace(cmd[pos]) && !flags->quote && !flags->braces && cmd[pos] != '\n')
				break ;
			++pos;
		}
		if (!cmd[pos])
			break ;
		cmd = ft_skip_space(&cmd[pos]);
		pos = 0;
	}
	return (len);
}

static void	collect_args_loop(char **array, char *cmd, t_token_flags *flags)
{
	int		i;
	int		pos;

	i = 0;
	pos = 0;
	while (cmd[pos])
	{
		while (cmd[pos])
		{
			quote_brace_check(cmd, pos, flags);
			if (ft_isspace(cmd[pos]) && !flags->quote && !flags->braces && cmd[pos] != '\n')
				break ;
			++pos;
		}
		array[i++] = ft_strsub(cmd, 0, pos);
		if (!cmd[pos])
			break ;
		cmd = ft_skip_space(&cmd[pos]);
		pos = 0;
	}
	array[i] = NULL;
}

static void	init_flags_struct(t_token_flags *flags)
{
	flags->quote = 0;
	flags->braces = 0;
	flags->braces_count = 0;
}

static int	arg_qty(char *cmd, t_token_flags *flags)
{
	int		len;
	char	*tofree;

	tofree = cmd;
	cmd = ft_skip_space(cmd);
	len = arg_qty_loop(cmd, flags);
	ft_strdel(&tofree);
	init_flags_struct(flags);
	return (len);
}


char	**make_arg_array(char *cmd)
{
	int		len;
	char	**array;
	t_token_flags	flags;

	init_flags_struct(&flags);
	len = arg_qty(ft_strdup(cmd), &flags);
	array = (char **)ft_memalloc(sizeof(char *) * (len + 1));
	cmd = ft_skip_space(cmd);
	collect_args_loop(array, cmd, &flags);
	return (array);
}
