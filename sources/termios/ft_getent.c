/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getent.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 08:42:47 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/26 09:55:24 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/**
 * It gets the terminal type from the environment, and then uses the termcap
 * library to get the terminal capabilities
 *
 * @return The number of lines in the terminal.
 */
int	ft_getent(void)
{
	char	*termtype;
	int		status;

	termtype = getenv("TERM");
	if (termtype == NULL)
	{
		ft_err_print(NULL, NULL, "could not get the TERM env", 2);
		exit(1);
	}
	status = tgetent(NULL, termtype);
	if (status < 0)
	{
		ft_err_print(NULL, NULL, "could not access the termcap data base", 2);
		exit(1);
	}
	else if (status == 0)
	{
		ft_err_print(NULL, NULL, "could not find the termtype", 2);
		exit(1);
	}
	return (status);
}
