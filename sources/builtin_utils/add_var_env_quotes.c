/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_var_env_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:59:28 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/15 20:19:11 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	add_var_env_quotes(char **cmd)
{
	char	*value;
	char	*key;
	char	*temp;

	value = ft_strchr((*cmd), '=');
	key = ft_strndup((*cmd), \
	ft_strlen((*cmd)) - ft_strlen(value) + 1);
	if (ft_strchr(value + 1, ' ') && value[1] != '\'')
	{
		temp = ft_strjoin("'", value + 1);
		value = ft_strjoin(temp, "'");
		ft_strdel(&temp);
		temp = ft_strjoin(key, value);
		ft_strdel(cmd);
		(*cmd) = ft_strdup(temp);
		ft_strdel(&temp);
		ft_strdel(&value);
	}
	ft_strdel(&key);
}
