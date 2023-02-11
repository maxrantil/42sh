/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:53:08 by spuustin          #+#    #+#             */
/*   Updated: 2023/02/10 20:57:53 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int	cd_multi_command_validation(t_shell *sh, char **commands)
{
	if (commands[1][0] != '-')
	{
		ft_err_print(NULL, "cd", "too many arguments", 1);
		sh->exit_stat = 1;
		return (1);
	}
	if (validate_cd_options(sh, commands, 1, 0) == 1)
	{
		sh->exit_stat = 1;
		return (1);
	}
	return (0);
}
