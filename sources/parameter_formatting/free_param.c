/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 09:01:24 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/08 22:31:00 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

char *sent_start(char *cmd)
{
	char *fresh;
	int	i;
	
	i = 0;
	fresh = ft_strnew(ft_strlen(cmd));
	while(cmd[i])
	{
		fresh[i] = cmd[i];
		i++;
		if (cmd[i] == '$')
			break ;
	}
	return (fresh);
}

void	free_er(t_param *pa, char **cmd, char *new_cmd, int *j)
{
	char *temp;
	char	*start;
	char	*end;

	start = sent_start(*cmd);
	end = ft_strdup(&(*cmd)[*j]);
	temp = ft_strjoin(start, pa->expanded);
	*j += ft_strlen(pa->expanded);
	ft_printf("%s\n",temp);
	ft_strdel(&(*cmd));
	*cmd = ft_strjoin(temp, end);
	ft_strdel(&pa->expanded);
	//ft_strdel(&pa->var);
	//ft_strdel(&pa->subs);
	ft_strdel(&temp);
	//ft_strdel(&pa->strip);
	ft_strdel(&start);
	ft_strdel(&end);
}