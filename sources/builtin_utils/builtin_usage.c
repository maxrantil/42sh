/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_usage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:22:13 by spuustin          #+#    #+#             */
/*   Updated: 2023/02/11 13:21:33 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	print_usage(char *command, char c)
{
	ft_printf("42sh: %s: -%c: invalid option\n", command, c);
	if (ft_strequ(command, "cd"))
		ft_printf("cd: usage: cd [-L | -P] [dir]\n");
	if (ft_strequ(command, "type"))
		ft_printf("type: usage: type name [name ...]\n");
	if (ft_strequ(command, "jobs"))
	{
		ft_printf("jobs: usage: jobs [-lp] [jobspec ...]");
		ft_printf(" or jobs -x command [args]\n");
	}
}
