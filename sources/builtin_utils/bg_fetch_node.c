/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_fetch_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:04:15 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/15 14:24:29 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static t_bg_jobs	*search_via_index(t_shell *sh, int index, char *cmd)
{
	t_bg_jobs	*head;

	head = sh->bg_node;
	while (head)
	{
		if (index == head->index)
			return (head);
		head = head->next;
	}
	ft_printf("42sh: %s: no such job\n", cmd);
	return (NULL);
}

static t_bg_jobs	*search_via_queue(t_shell *sh, char sign, char *cmd)
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
	ft_printf("42sh: %s: no such job\n", cmd);
	return (NULL);
}

t_bg_jobs	*bg_fetch_node(t_shell *sh, char *args, char *cmd)
{
	int	i;

	i = 0;
	if (!args || !ft_strcmp("%", args) \
	|| !ft_strcmp("%%", args) || !ft_strcmp("%+", args) \
	|| !ft_strcmp("+", args))
		return (search_via_queue(sh, '+', cmd));
	if (!ft_strcmp("%-", args) || !ft_strcmp("-", args))
		return (search_via_queue(sh, '-', cmd));
	if (args[i] == '%')
		++i;
	if (ft_isdigit(args[i]))
		return (search_via_index(sh, ft_atoi(&args[i]) - 1, cmd));
	else
		return (search_via_cmd(sh, args, cmd));
	return (NULL);
}
