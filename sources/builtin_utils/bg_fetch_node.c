/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_fetch_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:04:15 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/06 15:39:34 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"
/*
	How to refer to a job according to bash manual
	- Job index can be refered to by just number or %number
	- %% or % or %+ refer to the current job
	- %- refers to previous job
	- If there is only one job, then %- and %+ are will refer to the same job
	- %ce is to refer to a job whose command starts with 'ce'
	- %ce? refers to any job containing the string 'ce' in its command line.
	- If the prefix or substring matchers more than one job, report an error
	- Running fg %1 & -> is similar to bg %1 // sh->ampersand should be on here, that is what we use
*/

static t_bg_jobs    *search_via_index(t_shell *sh, int index, char **cmd)
{
	t_bg_jobs   *head;

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

static t_bg_jobs   *search_via_queue(t_shell *sh, char sign, char **cmd)
{
	int         count;
	int         target;
	t_bg_jobs   *head;

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

static t_bg_jobs   *search_via_cmd(t_shell *sh, char **cmd)
{
	int			i;
	t_bg_jobs   *ret;
	t_bg_jobs   *head;
	char        **command;
	bool        substring_flag;

	i = 0;
	ret = NULL;
	substring_flag = false;
	if (**(cmd + 1) == '?')
	{
		++i;
		substring_flag = true;
	}
	head = sh->bg_node;
	while (head)
	{
		command = NULL;
		if (substring_flag)
		{
			command = *head->cmd;
			while (*command)
			{
				if (ft_strstr(*command, &cmd[1][i]))
				{
					if (!ret)
						ret = head;
					else
					{
						ft_printf("42sh: %s: %s: ambiguous job spec\n", *cmd, &cmd[1][i]);
						return (NULL);
					}
				}
				++command;
			}
		}
		else
		{
			if (ft_strstr(**head->cmd, &cmd[1][i]))
			{
				if (!ret)
					ret = head;
				else
				{
					ft_printf("42sh: %s: %s: ambiguous job spec\n", *cmd, &cmd[1][i]);
					return (NULL);
				}
			}
		} 
		head = head->next;
	}
	if (!ret)
		ft_printf("42sh: %s: no such job\n", *cmd);	
	return (ret);
}

t_bg_jobs   *process_getpid(t_shell *sh, int index, char **cmd, char sign)
{
	if (sign)
		return (search_via_queue(sh, sign, cmd));
	if (index)
		return (search_via_index(sh, --index, cmd));
	return (search_via_cmd(sh, cmd));
}

t_bg_jobs    *bg_fetch_node(t_shell *sh, char **cmd)
{
	int	i;

	i = 0;	
	if (!*(cmd + 1) || !ft_strcmp("%", *(cmd + 1)) || !ft_strcmp("%%", *(cmd + 1)) || !ft_strcmp("%+", *(cmd + 1)))
		return (process_getpid(sh, 0, cmd, '+'));
	if (!ft_strcmp("%-", *(cmd + 1))) // fetch the first one in the queue
		return (process_getpid(sh, 0, cmd, '-'));
	if (**(cmd + 1) == '%')
		++i;
	if (ft_isdigit(**(cmd + 1)))
	{
		// ft_printf("isdigit %d\n", ft_atoi(&cmd[1][i]) - 1);
		return (process_getpid(sh, ft_atoi(&cmd[1][i]),  cmd, 0));
	}
	else
		return (process_getpid(sh, 0, cmd,  0));
	return (NULL);
}

// static t_bg_jobs    *search_via_index(t_shell *sh, int index)
// {
// 	t_bg_jobs   *head;

// 	head = sh->bg_node;
// 	while (head)
// 	{
// 		if (index == head->index)
// 			return (head);
// 		head = head->next;
// 	}
// 	return (NULL);
// }

// static t_bg_jobs   *search_via_queue(t_shell *sh, char sign)
// {
// 	int         count;
// 	int         target;
// 	t_bg_jobs   *head;

// 	count = 0;
// 	head = sh->bg_node;
// 	if (sign == '+')
// 		target = sh->process_queue[0];
// 	else
// 		target = sh->process_queue[1];
// 	while (head)
// 	{
// 		++count;
// 		if (head->index == target)
// 			return (head);
// 		head = head->next;
// 	}
// 	if (count == 1)
// 		return (sh->bg_node);
// 	return (NULL);
// }

// static t_bg_jobs   *search_via_cmd(t_shell *sh, char *cmd)
// {
// 	t_bg_jobs   *ret;
// 	t_bg_jobs   *head;
// 	char        **command;
// 	bool        substring_flag;

// 	ret = NULL;
// 	substring_flag = false;
// 	if (*cmd == '?')
// 	{
// 		substring_flag = true;
// 		++cmd;    
// 	}
// 	head = sh->bg_node;
// 	while (head)
// 	{
// 		command = NULL;
// 		if (substring_flag)
// 		{
// 			command = *head->cmd;
// 			while (*command)
// 			{
// 				if (ft_strstr(*command, cmd))
// 				{
// 					if (!ret)
// 						ret = head;
// 					else
// 					{
// 						ft_putstr_fd("42sh: fg: sle: ambiguous job spec\n", 2);   
// 						return (NULL);
// 					}
// 				}
// 				++command;
// 			}
// 		}
// 		else
// 		{
// 			if (ft_strstr(**head->cmd, cmd))
// 			{
// 				if (!ret)
// 					ret = head;
// 				else
// 				{
// 					ft_putstr_fd("42sh: fg: sle: ambiguous job spec\n", 2);   
// 					return (NULL);
// 				}
// 			}
// 		} 
// 		head = head->next;
// 	}
// 	return (ret);
// }

// t_bg_jobs   *process_getpid(t_shell *sh, int index, char *cmd, char sign)
// {
// 	if (cmd)
// 		return (search_via_cmd(sh, cmd));
// 	if (sign)
// 		return (search_via_queue(sh, sign));
// 	return (search_via_index(sh, index));
// }

// t_bg_jobs    *bg_fetch_node(t_shell *sh, char *cmd)
// {
// 	if (!cmd || !ft_strcmp("%", cmd) || !ft_strcmp("%%", cmd) || !ft_strcmp("%+", cmd))
// 		return (process_getpid(sh, 0, NULL, '+'));
// 	if (!ft_strcmp("%-", cmd)) // fetch the first one in the queue
// 		return (process_getpid(sh, 0, NULL, '-'));
// 	if (*cmd == '%')
// 		++cmd;
// 	if (ft_isdigit(*cmd))
// 		return (process_getpid(sh, ft_atoi(cmd) - 1,  NULL, 0));
// 	else
// 		return (process_getpid(sh, 0, cmd,  0));
// 	return (NULL);
// }
