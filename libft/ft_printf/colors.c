/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 18:15:51 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/14 11:38:18 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	write_colors(t_ftprintf *data)
{
	int		i;
	char	colorcode[8];

	i = 1;
	ft_strcpy(colorcode, "\x1B[0;3im");
	if (data->fmt[4] == '}')
	{
		if (data->fmt[1] == 'n')
		{
			(void)(write(1, "\x1B[0;0m", 6) + 1);
			data->fmt += 5;
			return ;
		}
		while (data->fmt[1] != PF_COLORS[i])
			i++;
		colorcode[5] = i + '0';
		(void)(write(1, colorcode, 7) + 1);
		data->fmt += 5;
	}
}
