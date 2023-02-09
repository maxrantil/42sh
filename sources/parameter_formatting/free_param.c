/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 09:01:24 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/09 21:02:40 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

char *sent_start(char *cmd)
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

void	free_er(t_param *pa, char **cmd, char **subst_cmd, int *j)
{
	char	*temp;
	char	*start;
	char	*end;

	(void)subst_cmd;
	start = sent_start(*cmd);
	end = ft_strdup(&(*cmd)[*j]);
	temp = ft_strjoin(start, pa->expanded);
	*j = ft_strlen(temp) - 1;
	ft_strdel(&(*cmd));
	(*cmd) = ft_strjoin(temp, end);
	if (!ft_strchr(*cmd, '$'))
		*j = ft_strlen(*cmd) - 1;
	ft_strdel(&pa->expanded);
	if (pa->var)
		ft_strdel(&pa->var);
	if (pa->subs)
		ft_strdel(&pa->subs);
	ft_strdel(&temp);
	if (pa->strip)
		ft_strdel(&pa->strip);
	ft_strdel(&start);
	ft_strdel(&end);
}

