/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 09:08:01 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/11 11:20:33 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int	format_mode(char op)
{
	int		format;

	format = -1;
	if (op == '-')
		format = USE_DEFAULT;
	else if (op == '=')
		format = ASSIGN_DEFAULT;
	else if (op == '?')
		format = DISPLAY_ERR;
	else if (op == '+')
		format = ALTERNATE_VALUE;
	return (format);
}
