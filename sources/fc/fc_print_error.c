/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:17:44 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/24 09:56:48 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	fc_print_error(int check)
{
	if (check == 1)
		ft_putendl_fd("42sh: No editor found. Please set FCEDIT or EDITOR.", 2);
	else if (check == 2)
		ft_putendl_fd("42sh: Could not open file for editing.", 2);
	else if (check == 3)
	{
		ft_putendl_fd("42sh: Error malloc, in ft_strsplit() from ft_fc().", 2);
		exit(1);
	}
	else if (check == 4)
		ft_putendl_fd("42sh: Could not open file for editing.", 2);
	else if (check == 5)
		ft_putendl_fd("42sh: fc: no command found", 2);
	return (0);
}
