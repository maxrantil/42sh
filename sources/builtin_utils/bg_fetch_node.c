/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_fetch_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:04:15 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/08 20:11:50 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static t_bg_jobs	*search_via_index(t_shell *sh, int index, char **cmd)
{
	t_bg_jobs	*head;

	head = sh->bg_node;
	while (head)
	{
		if (index == head->index)
			return (head);
		head = head->next;
	}
	ft_printf("42sh: %s: no such job\n", *cmd);
	return (NULL);
}

static t_bg_jobs	*search_via_queue(t_shell *sh, char sign, char **cmd)
{
	int			count;
	int			target;
	t_bg_jobs	*head;

	count = 0;
	head = sh->bg_node;
	if (sign == '+')
		target = sh->process_queue[0];
	else
		target = sh->process_queue[1];
	while (head)
	{
		++count;
		if (head->index == target)
			return (head);
		head = head->next;
	}
	if (count == 1)
		return (sh->bg_node);
	ft_printf("42sh: %s: no such job\n", *cmd);
	return (NULL);
}

t_bg_jobs	*process_getpid(t_shell *sh, int index, char **cmd, char sign)
{
	if (sign)
		return (search_via_queue(sh, sign, cmd));
	if (index)
		return (search_via_index(sh, --index, cmd));
	return (search_via_cmd(sh, cmd));
}

t_bg_jobs	*bg_fetch_node(t_shell *sh, char **cmd)
{
	int	i;

	i = 0;
	if (!*(cmd + 1) || !ft_strcmp("%", *(cmd + 1)) \
	|| !ft_strcmp("%%", *(cmd + 1)) || !ft_strcmp("%+", *(cmd + 1)))
		return (process_getpid(sh, 0, cmd, '+'));
	if (!ft_strcmp("%-", *(cmd + 1)))
		return (process_getpid(sh, 0, cmd, '-'));
	if (cmd[1][i] == '%')
		++i;
	if (ft_isdigit(cmd[1][i]))
		return (process_getpid(sh, ft_atoi(&cmd[1][i]), cmd, 0));
	else
		return (process_getpid(sh, 0, cmd, 0));
	return (NULL);
}
