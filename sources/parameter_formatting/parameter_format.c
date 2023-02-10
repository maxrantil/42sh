/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:40:05 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/10 11:53:10 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int check_syntax(char *cmd)
{
	int len;

	if (!cmd)
		return 0;
	len = ft_strlen(cmd) - 1;
	if (ft_strnequ(cmd, "${", 2) && cmd[len] == '}')
		return (1);
	return (0);
}



static char *separate_form(char *cmd)
{
	char *fresh;
	int i;
	int k;
	int open;

	i = -1;
	k = 0;
	open = 0;
	fresh = ft_strnew(100);
	while (cmd[++i])
	{
		fresh[k++] = cmd[i];
		if (cmd[i] == '{')
			open += 1;
		else if (cmd[i] == '}')
			open -= 1;
		if (cmd[i] == '}' && open == 0)
		{
			break;
		}
	}
	return (fresh);
}

static char	*init_form_cycle(t_param *pa, char *cmd, t_pa_ints *ints)
{
	char *new_cmd;
	init_pa(pa);
	ints->ret = 0;
	new_cmd = NULL;
	if (ft_strnequ(&cmd[ints->j], "${", 2))
	{
		new_cmd = separate_form(&cmd[ints->j]);
		ints->j += ft_strlen(new_cmd);
	}
	return (new_cmd);
}

int param_format(char **cmd)
{
	t_param pa;
	t_pa_ints ints;
	char *new_cmd;

	init_pa_ints(&ints, &new_cmd);
	while (cmd[++ints.i])
	{
		while (cmd[ints.i][ints.j])
		{
			new_cmd = init_form_cycle(&pa, cmd[ints.i], &ints);
			if (check_syntax(new_cmd))
			{
				if (perform_param_expans(new_cmd, &pa, &ints.ret) == 0)
					substitute_og_cmd(&pa, &cmd[ints.i], &ints.j);
				else
					break ;
			}
			if (cmd[ints.i] && cmd[ints.i][ints.j])
				ints.j++;
			free_attrs(&pa, &new_cmd);
		}
		ints.j = 0;
	}
	return (ints.err);
}
