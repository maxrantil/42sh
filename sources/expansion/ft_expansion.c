/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:33:11 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/16 17:33:14 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static char	*look_for_expansion(t_shell *sh, char **cmd, int i)
{
	if (ft_strchr(cmd[i], '$') && ft_strlen(cmd[i]) > 1)
		return (ft_expansion_dollar(sh, cmd[i]));
	else if (**(cmd + i) == '~')
		return (ft_expansion_tilde(sh, cmd[i]));
	return (NULL);
}

/**
 * It loops through each word in the command, and if it finds a dollar sign,
 * it expands the variable.
 *
 * @param sh the session struct
 * @param cmd the command to be expanded
 */
void	ft_expansion(t_shell *sh, char **cmd)
{
	int		i;
	char	*expanded;
	char	*buff;

	i = -1;
	buff = NULL;
	while (cmd[++i])
	{
		expanded = NULL;
		expanded = look_for_expansion(sh, cmd, i);
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
