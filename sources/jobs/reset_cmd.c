/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:20:34 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/02 16:20:51 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	reset_cmd(char ****cmd)
{
	char	***tofree;

    tofree = *cmd;
    while (*tofree)
    {
        ft_arrclean(*tofree);
        ++tofree;
    }
    ft_memdel((void **)&(*cmd));
}
