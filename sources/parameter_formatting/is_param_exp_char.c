/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_param_exp_char.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:15:36 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/13 11:42:54 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int is_param_exp_char(char *flag)
{
	if (*flag == '\0')
		return (0);
	else if (flag[0] == ':')
		return (flag[1] == '-' || flag[1] == '+'
			|| flag[1] == '=' || flag[1] == '?');
	return ((flag[0] == '%' && flag[1]) || (flag[0] == '#' && flag[1]));
}
