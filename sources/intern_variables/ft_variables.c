/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_variables.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:54:26 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/02 19:26:05 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int is_var(char *cmd)
{
	return ((ft_strchr(cmd, '=') && ft_isalpha(cmd[0]))
		|| (ft_strchr(cmd, '=') && !ft_isalpha(cmd[0]) && cmd[0] == '_'));
}

int ft_variables(t_shell *sh, char ***cmd)
{
	int ret;
	int	i;

	i = 0;
	ret = 0;
	if (is_var(**cmd))
	{
		ret = add_var(sh, *cmd);
		while(sh->intr_vars[i])
			ft_printf("intern var %s %c\n", sh->intr_vars[i++], **cmd[0]);
	}
	return (ret);
}
