/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_arg_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 21:59:23 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/16 17:21:41 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static char	*find_end_arg(char *cmd)
{
	int	qoute;

	qoute = 0;
	while (*cmd)
	{
		if (*cmd == '"' || *cmd == '\'')
		{
			if (!qoute)
				qoute = *cmd;
			else if (qoute == *cmd)
				qoute = 0;
		}
		else if (ft_isspace(*cmd) && !qoute && *cmd != '\n')
			break ;
		++cmd;
	}
	return (cmd);
}

static int	arg_qty_loop(char *cmd)
{
	int	len;

	len = 0;
	while (cmd)
	{
		len++;
		cmd = find_end_arg(cmd);
		cmd = ft_skip_space(cmd);
	}
	return (len);
}

static void	collect_args_loop(char **array, char *cmd)
{
	int		i;
	char	*ptr;

	i = 0;
	while (cmd)
	{
		ptr = find_end_arg(cmd);
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
