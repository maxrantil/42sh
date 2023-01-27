/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_is_unary.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:30:29 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/27 11:20:16 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
	These are mandatory:
	-c, -d, -e, -f, -g, -L, -p, -r, -S, -s, -u, -w, -x, -z, !
*/
int	ft_test_is_unary(char *str)
{
	return (ft_strequ(str, "-c") || ft_strequ(str, "-d")
		|| ft_strequ(str, "-e") || ft_strequ(str, "-f")
		|| ft_strequ(str, "-g") || ft_strequ(str, "-L")
		|| ft_strequ(str, "-p") || ft_strequ(str, "-r")
		|| ft_strequ(str, "-S") || ft_strequ(str, "-s")
		|| ft_strequ(str, "-u") || ft_strequ(str, "-w")
		|| ft_strequ(str, "-x") || ft_strequ(str, "-z"));
}
