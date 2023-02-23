/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_og_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 09:01:24 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/23 09:30:00 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static char	*sent_start(char *cmd)
{
	char	*fresh;
	int		i;

	i = 0;
	fresh = ft_strnew(ft_strlen(cmd));
	if (cmd[i] == '$')
		return (fresh);
	while (cmd[i])
	{
		fresh[i] = cmd[i];
		i++;
		if (cmd[i] == '$')
			break ;
	}
	return (fresh);
}

static void	free_all(t_param *pa, char **temp, char **start, char **end)
{
	if (pa->var)
		ft_strdel(&pa->var);
	if (pa->subs)
		ft_strdel(&pa->subs);
	ft_strdel(&(*temp));
	if (pa->strip)
		ft_strdel(&pa->strip);
	ft_strdel(&(*start));
	ft_strdel(&(*end));
}

void	substitute_og_cmd(t_param *pa, char **cmd, int *j)
{
	char	*temp;
	char	*start;
	char	*end;

	start = NULL;
	temp = NULL;
	end = NULL;
	start = sent_start(*cmd);
	end = ft_strdup(&(*cmd)[*j]);
	temp = ft_strjoin(start, pa->expanded);
	//ft_printf("start [%s] end [%s] te,p [%s] \n", start, end, temp);
	*j = ft_strlen(temp);
	ft_strdel(&(*cmd));
	(*cmd) = ft_strjoin(temp, end);
	(*j)--;
	if (*j < 0)
		*j = 0;
	free_all(pa, &temp, &start, &end);
}
