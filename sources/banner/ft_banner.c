/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_banner.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:31:02 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/25 16:42:34 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	banner_padding(size_t str_len)
{
	struct winsize	arg;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &arg) < 0)
	{
		ft_err_print(NULL, NULL, "could not get the terminal size", 2);
		exit(1);
	}
	return ((arg.ws_col - str_len) >> 1);
}

static void	jakke_and_mikey(void)
{
	int		padd;
	char	*str;

	str = "       __      __   __        ___     __  ____ __      ";
	padd = banner_padding(ft_strlen(str));
	ft_printf("\n%*s%s\n", padd, "", str);
	ft_printf("%*s%s\n", padd, "",
		"      42sh, lets do this! ");
}

static void	banner(void)
{
	int		padd;
	char	*str;

	str = "        _      _    _        _ _ ";
	padd = banner_padding(ft_strlen(str));
	ft_printf("%*s%s\n", padd, "", str);
	ft_printf("%*s%s\n", padd, "",
		"      42sh, lets do this! ");
}

void	banner_print(void)
{
	ft_run_capability("cl");
	jakke_and_mikey();
	banner();
}
