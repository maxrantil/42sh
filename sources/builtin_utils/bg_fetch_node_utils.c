/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_fetch_node_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:20:42 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/07 17:24:23 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static bool	substring_search(t_bg_jobs	**ret, t_bg_jobs *head, \
char *arg, char *cmd)
{
	char	**command;

	command = *head->cmd;
	while (*command)
	{
		if (ft_strstr(*command, cmd))
		{
			if (!*ret)
			{
				*ret = head;
				return (true);
			}
			else
			{
				ft_printf("42sh: %s: %s: ambiguous job spec\n", *arg, cmd);
				return (false);
			}
		}
		++command;
	}
	return (true);
}

static bool	prefix_search(t_bg_jobs	**ret, t_bg_jobs *head, \
char *arg, char *cmd)
{
	if (ft_strstr(**head->cmd, cmd))
	{
		if (!*ret)
			*ret = head;
		else
		{
			ft_printf("42sh: %s: %s: ambiguous job spec\n", *arg, cmd);
			return (false);
		}
	}
	return (true);
}

static int	get_start_point(char **cmd, bool *substring_flag)
{
	int	i;

	i = 0;
	*substring_flag = false;
	if (cmd[1][i] == '%')
	{
		++i;
		if (cmd[1][i] == '?')
		{
			++i;
			*substring_flag = true;
		}
	}
	return (i);
}

t_bg_jobs	*search_via_cmd(t_shell *sh, char **cmd)
{
	int			i;
	t_bg_jobs	*ret;
	t_bg_jobs	*head;
	bool		substring_flag;

	ret = NULL;
	i = get_start_point(cmd, &substring_flag);
	head = sh->bg_node;
	while (head)
	{
		if (substring_flag)
		{
			if (!substring_search(&ret, head, *cmd, &cmd[1][i]))
				return (NULL);
		}
		else
		{
			if (!prefix_search(&ret, head, *cmd, &cmd[1][i]))
				return (NULL);
		}
		head = head->next;
	}
	if (!ret)
		ft_printf("42sh: %s: no such job\n", *cmd);
	return (ret);
}
