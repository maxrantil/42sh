/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_variables.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:54:26 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/25 16:30:43 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int is_var(char *cmd)
{
	return ((ft_strchr(cmd, '=') && ft_isalpha(cmd[0]))
		|| (ft_strchr(cmd, '=') && !ft_isalpha(cmd[0]) && cmd[0] == '_'));
}

int ft_variables(t_session *sesh, char ***cmd)
{
	int ret;
	int	i;

	i = 0;
	ret = 0;
	if (is_var(**cmd))
	{
		ret = add_var(sesh, *cmd);
		while(sesh->intr_vars[i])
			ft_printf("intern var %s %c\n", sesh->intr_vars[i++], **cmd[0]);
	}
	//ft_printf("%d\n", ret);
	return (ret);
}
