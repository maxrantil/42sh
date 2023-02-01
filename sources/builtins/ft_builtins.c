/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/02/01 14:47:03 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	print_fg_node(t_shell *sh)
{
	pid_t	*tmp;
	char	***ptr;
	char	**dbl;

	ft_printf("gpid %d\n", sh->fg_node->gpid);
	tmp = sh->fg_node->pid;
	while (tmp && *tmp)
		ft_printf("pid: %d\n", *(tmp++));
	ptr = sh->fg_node->cmd;
	while (ptr && *ptr)
	{
		dbl = *ptr;
		while (*dbl)
        {
			ft_printf("cmd: %s\n", *dbl);
            dbl++;
        }
        ptr++;
	}
	return (0);
}

static int	ft_jobs(t_shell *sh)
{
	t_bg_jobs *job;
	pid_t	*tmp;
	char	***ptr;
	char	**dbl;

	job = sh->bg_node;
	while (job)
	{
		ft_printf("index %d\n", job->index);
		ft_printf("status %d\n", job->status);
		ft_printf("gpid %d\n", job->gpid);
		tmp = job->pid;
		while (tmp && *tmp)
			ft_printf("pid: %d\n", *(tmp++));
		ptr = job->cmd;
		while (ptr && *ptr)
		{
			dbl = *ptr;
			while (*dbl)
			{
				ft_printf("cmd: %s\n", *dbl);
				dbl++;
			}
			ptr++;
		}
		job = job->next;
	}	
	return (0);
}

/**
 * It takes a session and a command, expands the command, and then checks if
 * the command is a builtin. If it is, it runs the builtin and returns the exit
 * status. If it's not, it returns 1.
 *
 * @param sh the session struct
 * @param cmd The command to be executed.
 *
 * @return The return value of the builtin function.
 */
int	ft_builtins(t_shell *sh, char ***cmd)
{
	if (sh && cmd)
	{
		ft_expansion(sh, *cmd);
		ft_env_last_command(sh, *cmd);
		if (param_format(sh, *cmd) == -1)
			return (0);
		*(cmd) += ft_variables(sh, cmd);
		if (**cmd == NULL)
			return (0);
		else if (**cmd && !ft_strcmp(**cmd, "set"))
			return (ft_set(sh, cmd));
		else if (**cmd && !ft_strcmp(**cmd, "export"))
			return (ft_export(sh, *cmd));
		else if (**cmd && !ft_strcmp(**cmd, "unset"))
			return (ft_unset(sh, *cmd));
		else if (**cmd && !ft_strcmp(**cmd, "cd"))
			return (ft_cd(sh, *cmd));
		else if (**cmd && !ft_strcmp(**cmd, "echo"))
			return (ft_echo(sh, *cmd));
		else if (!ft_strcmp(**cmd, "history"))
			return (ft_history(sh->term, *cmd));
		else if (!ft_strcmp(**cmd, "fc"))
			return (ft_fc(sh, cmd));
		else if (!ft_strcmp(**cmd, "test"))
			return(ft_test(sh, *cmd));
		else if (!ft_strcmp(**cmd, "hash"))
			return (ft_hash(sh, *cmd));
		else if (!ft_strcmp(**cmd, "exit"))
			ft_exit(sh, 0);
		else if (!ft_strcmp(**cmd, "fg"))
			return (print_fg_node(sh));
		else if (!ft_strcmp(**cmd, "jobs"))
			return (ft_jobs(sh));
	}
	return (1);
}
