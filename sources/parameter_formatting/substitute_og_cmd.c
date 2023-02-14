/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_og_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 09:01:24 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/13 15:06:33 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static char *sent_start(char *cmd)
{
	char *fresh;
	int	i;
	
	i = 0;
	fresh = ft_strnew(ft_strlen(cmd));
	if (cmd[i] == '$')
		return fresh;
	while(cmd[i])
	{
		fresh[i] = cmd[i];
		i++;
		if (cmd[i] == '$')
			break ;
	}
	return (fresh);
}

static void free_all(t_param *pa, char **temp, char **start, char **end)
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

	start = sent_start(*cmd);
	end = ft_strdup(&(*cmd)[*j]);
	temp = ft_strjoin(start, pa->expanded);
	*j = ft_strlen(temp) - 1;
	ft_strdel(&(*cmd));
	(*cmd) = ft_strjoin(temp, end);
	if (!ft_strchr(*cmd, '$'))
		*j = ft_strlen(*cmd) - 1;
	ft_strdel(&pa->expanded);
	pa->expanded = ft_strtrim((*cmd));
	if (!pa->expanded)
		pa->expanded = ft_strnew(1);
	ft_strdel(&(*cmd));
	(*cmd) = ft_strdup(pa->expanded);
	ft_strdel(&pa->expanded);
	*j += ft_strlen(*cmd) - ft_strlen(temp);
	if (*j >= (int)ft_strlen(*cmd))
		*j = ft_strlen(*cmd) - 1;
	free_all(pa, &temp, &start, &end);
}

