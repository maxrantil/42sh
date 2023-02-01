/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_job_print_dbl_array.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:04:31 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/01 15:06:08 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/**
 * It prints a double array of strings
 * 
 * @param cmd The array of strings to print
 */
void ft_print_dbl_array(char **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		ft_printf("%s", cmd[i]);
		if (cmd[i + 1])
			ft_printf(" ");
	}
}
