/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_banner.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:31:02 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/16 15:27:01 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/* static int	banner_padding(size_t str_len)
{
	struct winsize	arg;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &arg) < 0)
	{
		ft_err_print(NULL, NULL, "could not get the terminal size", 2);
		exit(1);
	}
	return ((arg.ws_col - str_len) >> 1);
} */

/* static void	banner(void)
{
	int		padd;
	char	*str;

	str = ft_strdup("42sh, lets do this!");
	padd = banner_padding(ft_strlen(str));
	ft_printf("%*s%s\n", padd, "",
		"      42sh, lets do this! ");
	ft_strdel(&str);
} */

void	banner_print(void)
{
	ft_run_capability("cl");
	/* banner(); */
}
