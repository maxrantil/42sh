/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_and_remove_null.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:17:09 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/16 18:12:55 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	delete_null_param(char ****cmd, t_pa_ints *ints)
{
	char	*temp;

	while ((**cmd)[ints->i])
	{
		ft_strdel(&(**cmd)[ints->i]);
		if ((**cmd)[ints->i + 1])
			temp = (**cmd)[ints->i + 1];
		else
			return (1);
		(**cmd)[ints->i] = ft_strdup(temp);
		ints->i++;
	}
	return (0);
}

void	trim_and_remove_null(char ***cmd, t_pa_ints *ints)
{
	char	*trimmed;
	int		k;

	trimmed = ft_strtrim((*cmd)[ints->i]);
	if (!trimmed && ints->i > 0)
	{
		k = ints->i;
		if (!delete_null_param(&cmd, ints))
			return ;
		ints->i = k - 1;
		if (ints->i < 0)
			ints->i = 0;
	}
	else if (trimmed && ints->i > 0)
	{
		ft_strdel(&(*cmd)[ints->i]);
		(*cmd)[ints->i] = ft_strdup(trimmed);
		ft_strdel(&trimmed);
	}
	else
		ft_strdel(&trimmed);
}
