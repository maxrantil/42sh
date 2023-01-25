/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/01/25 15:44:21 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_21sh.h"

static char	*look_for_expansion(t_session *sesh, char **cmd, int i)
{
	if (*cmd[i] != '\'' && ft_strchr(cmd[i], '$') && ft_strlen(cmd[i]) > 1)
		return (ft_expansion_dollar(sesh, cmd[i]));
	else if (**(cmd + i) == '~')
		return (ft_expansion_tilde(sesh, cmd[i]));
	return (NULL);
}

/**
 * It loops through each word in the command, and if it finds a dollar sign,
 * it expands the variable.
 *
 * @param sesh the session struct
 * @param cmd the command to be expanded
 */
void	ft_expansion(t_session *sesh, char **cmd)
{
	int		i;
	char	*expanded;
	char	*buff;

	i = -1;
	buff = NULL;
	while (cmd[++i])
	{
		expanded = NULL;
		expanded = look_for_expansion(sesh, cmd, i);
		if (!expanded)
			buff = ft_strdup(cmd[i]);
		else
		{
			buff = ft_strdup(expanded);
			ft_strdel(&expanded);
		}
		ft_strdel(cmd + i);
		ft_quote_blash_removal(buff);
		cmd[i] = ft_strdup(buff);
		ft_strdel(&buff);
	}
}
