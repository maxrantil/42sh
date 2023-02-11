/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_arg_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 21:59:23 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/11 14:00:35 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	quote_brace_check(char *qoute, char *brace, int *brace_count, \
char *cmd)
{
	if (*cmd == S_QUO || *cmd == D_QUO)
	{
		if (!*qoute)
			*qoute = *cmd;
		else if (*qoute == *cmd)
			*qoute = 0;
	}
	if (*cmd == L_BRAC || *cmd == R_BRAC)
	{
		if (!*brace || *brace == *cmd)
		{
			++(*brace_count);
			*brace = *cmd;
		}
		else if (*brace != *cmd)
		{
			if (*brace_count)
				--(*brace_count);
			else
				*brace = 0;
		}
	}
}

static int	arg_qty_loop(char *cmd)
{
	int		len;
	char	qoute;
	char	brace;
	int		brace_count;

	len = 0;
	qoute = 0;
	brace = 0;
	brace_count = 0;
	while (cmd)
	{
		len++;
		while (*cmd)
		{
			quote_brace_check(&qoute, &brace, &brace_count, cmd);
			if (ft_isspace(*cmd) && !qoute && !brace && *cmd != '\n')
				break ;
			++cmd;
		}
		cmd = ft_skip_space(cmd);
	}
	return (len);
}

static void	collect_args_loop(char **array, char *cmd)
{
	int		i;
	char	*ptr;
	char	qoute;
	char	brace;
	int		brace_count;

	i = 0;
	qoute = 0;
	brace = 0;
	brace_count = 0;
	while (cmd)
	{
		ptr = cmd;
		while (*ptr)
		{
			quote_brace_check(&qoute, &brace, &brace_count, ptr);
			if (ft_isspace(*ptr) && !qoute && !brace && *ptr != '\n')
				break ;
			++ptr;
		}
		array[i++] = ft_strsub(cmd, 0, (size_t)(ptr - cmd));
		cmd = ptr;
		cmd = ft_skip_space(cmd);
	}
	array[i] = NULL;
}

static int	arg_qty(char *cmd)
{
	int		len;
	char	*tofree;

	tofree = cmd;
	cmd = ft_skip_space(cmd);
	len = arg_qty_loop(cmd);
	ft_strdel(&tofree);
	return (len);
}

char	**make_arg_array(char *cmd)
{
	int		len;
	char	**array;

	len = arg_qty(ft_strdup(cmd));
	array = (char **)ft_memalloc(sizeof(char *) * (len + 1));
	cmd = ft_skip_space(cmd);
	collect_args_loop(array, cmd);
	return (array);
}
