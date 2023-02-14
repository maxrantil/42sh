/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_variables.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:54:26 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/14 12:53:34 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int ft_variables(t_shell *sh, char ***cmd)
{
	int ret;

	ret = 0;
	if (is_var(**cmd))
		ret = add_var(sh, *cmd);
	return (ret);
}
