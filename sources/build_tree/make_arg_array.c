/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_arg_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 21:59:23 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/13 18:07:11 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	arg_qty_loop(char *cmd, t_token_flags *flags)
{
	int	pos;
	int	len;

	pos = 0;
	len = 0;
	while (cmd[pos])
	{
		len++;
		while (cmd[pos])
		{
			tok_quote_flag(cmd, &pos, flags);
			if (ft_isspace(cmd[pos - 1]) && !flags->quote \
			&& !flags->braces && cmd[pos - 1] != '\n')
			{
				--pos;
				break ;
			}
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
			tok_quote_flag(cmd, &pos, flags);
			if (ft_isspace(cmd[pos - 1]) && !flags->quote \
			&& !flags->braces && cmd[pos - 1] != '\n')
			{
				--pos;
				break ;
			}
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
	int				len;
	char			**array;
	t_token_flags	flags;

	init_flags_struct(&flags);
	len = arg_qty(ft_strdup(cmd), &flags);
	array = (char **)ft_memalloc(sizeof(char *) * (len + 1));
	cmd = ft_skip_space(cmd);
	collect_args_loop(array, cmd, &flags);
	return (array);
}
