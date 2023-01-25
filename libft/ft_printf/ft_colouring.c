/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colouring.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 07:56:21 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/04 16:41:44 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define COLOUR_COUNT 15

static	void	init_colour_name(t_colours *colours)
{
	colours[0].name = "BLACK";
	colours[1].name = "RED";
	colours[2].name = "GREEN";
	colours[3].name = "YELLOW";
	colours[4].name = "BLUE";
	colours[5].name = "MAGENTA";
	colours[6].name = "CYAN";
	colours[7].name = "B_BLACK";
	colours[8].name = "B_RED";
	colours[9].name = "B_GREEN";
	colours[10].name = "B_YELLOW";
	colours[11].name = "B_BLUE";
	colours[12].name = "B_MAGENTA";
	colours[13].name = "B_CYAN";
	colours[14].name = "RESET";
}

static	void	init_colour_code(t_colours *colours)
{
	colours[0].code = "\033[0;30m";
	colours[1].code = "\033[0;31m";
	colours[2].code = "\033[0;32m";
	colours[3].code = "\033[0;33m";
	colours[4].code = "\033[0;34m";
	colours[5].code = "\033[0;35m";
	colours[6].code = "\033[0;36m";
	colours[7].code = "\033[1;30m";
	colours[8].code = "\033[1;31m";
	colours[9].code = "\033[1;32m";
	colours[10].code = "\033[1;33m";
	colours[11].code = "\033[1;34m";
	colours[12].code = "\033[1;35m";
	colours[13].code = "\033[1;36m";
	colours[14].code = "\033[0m";
}

static	int	get_end(char *format)
{
	int	ret;

	ret = 0;
	format++;
	while (format[ret] != '}')
		ret++;
	return (ret);
}

char	*coloring(char *format, int *char_count)
{
	int			i;
	int			end;
	t_colours	colours[COLOUR_COUNT];

	i = 0;
	end = get_end(format);
	init_colour_name(colours);
	init_colour_code(colours);
	while (i < COLOUR_COUNT)
	{
		if (ft_strncmp(format + 1, colours[i].name, end) == 0)
		{
			*char_count += ft_printf("%s", colours[i].code);
			return (&format[end + 2]);
		}
		i++;
	}
	return (format);
}
