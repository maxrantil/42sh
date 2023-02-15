/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_usage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:07:45 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/15 16:18:03 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int	fc_usage(char *str)
{
	ft_putstr_fd("42sh: fc: ", 2);
	ft_putendl_fd(str, 2);
	ft_putstr_fd("fc: usage: fc [-e ename] [-lnr] ", 2);
	ft_putendl_fd("[first] [last] or fc -s [pat=rep] [command]", 2);
	return (-1);
}
