/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 09:41:05 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/03 15:44:37 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/* static int	check_if_valid_input(t_fc *fc, char ***cmd)
{
	if ((*cmd && !(*cmd)[1 + fc->e]) \
		|| (*cmd && (*cmd)[1 + fc->e] \
		&& (*cmd)[1 + fc->e][0] == '-' \
		&& ft_isdigit((*cmd)[1 + fc->e][1])) \
		|| (*cmd && (*cmd)[1 + fc->e] && ft_isdigit((*cmd)[1 + fc->e][0])) \
		|| (*cmd && fc->e))
	{
		return (1);
	}
	return (0);
} */

/* static int	inner_loop(char ***cmd, int i, int j)
{
	while ((*cmd)[i][++j])
	{
		if (j == 0 && (*cmd)[i][0] == '-')
			continue ;
		else if (!ft_isdigit((*cmd)[i][j]))
		{
			if (j == 0 || (j == 1 && (*cmd)[i][0] == '-'))
			{
				ft_putendl_fd("42sh: fc: no command found", 2);
				return (1);
			}
			else
			{
				(*cmd)[i][j] = '\0';
				break ;
			}
		}
	}
	return (0);
} */

/* static int	check_for_errors(char ***cmd)
{
	int		i;
	int		j;

	i = 0;
	while ((*cmd)[++i] && i < 3)
	{
		j = -1;
		if (inner_loop(cmd, i, j))
			return (1);
	}
	return (0);
} */

void		printf_flags(t_fc *fc)
{
	if (fc->l == true)
		ft_printf("l flag is on\n");
	if (fc->r == true)
		ft_printf("r flag is on\n");
	if (fc->s == true)
		ft_printf("s flag is on\n");
	if (fc->e)
		ft_printf("e flag is on\n");
	if (fc->n == true)
		ft_printf("n flag is on\n");
}

static void fc_init_flags(t_fc *fc)
{
	fc->l = false;
	fc->r = false;
	fc->s = false;
	fc->e = 0;
	fc->n = false;
	fc->flags = 0;
}

int	ft_fc(t_shell *sh, char ***cmd)
{
	t_fc	fc;
	int		ret;

	fc_init_flags(&fc);
	if (!fc_get_flags(&fc, *cmd))
		return (0);
	ret = 0;
	if (fc.s)
		return (fc_s_flag(sh, &fc, cmd));
	/* if (check_if_valid_input(&fc, cmd))
	{
		if (check_for_errors(cmd))
			return (0);
		if (fc_error_check_for_no_flag_or_e_flag(sh, &fc, cmd))
			ret = fc_no_flag_or_e_flag(sh, &fc, cmd);
	}
	else
		ret = fc_check_flags(sh, cmd); */
	(void)sh;
	fc_init_flags(&fc);
	return (ret);
}
