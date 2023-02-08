/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:50:32 by jniemine          #+#    #+#             */
/*   Updated: 2023/02/08 12:14:46 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
*	ERRORS:
*	If more than 3 params
*	(two operands and operator I.E file1 -nt file2 is the max)
*		msg: 42sh: test: too many arguments
*	If 3 params, it is expected that second param is one of the binary
*	operators, first and third are treated as operands. If not:
*		msg: 42sh: <second param>: binary operator expected
*	If 2 params, it is expected that first param is one of the unary operators,
*	second one is treated as operand. If not:
*		msg: 42sh: <first param>: unary operator expected
*	Only one operator is allowed,
*	so for example in: test -fe, -fe is treated as operand.
*/
static int	validate_input(t_shell *sh, char **cmd, int punctuation)
{
	int		argc;

	argc = ft_arrlen(cmd);
	if (argc > (4 + punctuation))
		ft_err_print(NULL, "test", "too many arguments", 2);
	else if (argc == (4 + punctuation) \
			&& !ft_test_is_binary(cmd[2 + punctuation]))
		ft_err_print("test", cmd[3 + punctuation], \
		"binary operator expected", 2);
	else if (argc == (3 + punctuation) \
			&& !ft_test_is_unary(cmd[1 + punctuation]))
		ft_err_print("test", cmd[1 + punctuation], \
		"unary operator expected", 2);
	else if (argc <= (2 + punctuation))
		ft_putstr_fd("42sh: test: too few arguments, need spaces between arguments\n", 2);
	else
		return (0);
	sh->exit_stat = 2;
	return (1);
}

static int	operator_dispatcher_continue(char **cmd, int punctuation)
{
	if (ft_strequ(cmd[1 + punctuation], "-u"))
		return (ft_test_u(cmd));
	else if (ft_strequ(cmd[1 + punctuation], "-w"))
		return (ft_test_w(cmd));
	else if (ft_strequ(cmd[1 + punctuation], "-x"))
		return (ft_test_x(cmd));
	else if (ft_strequ(cmd[1 + punctuation], "-z"))
		return (ft_test_z(cmd));
	else if (ft_strequ(cmd[2 + punctuation], "!="))
		return (ft_test_not_equal(cmd));
	else if (ft_strequ(cmd[2 + punctuation], "-eq"))
		return (ft_test_eq(cmd));
	else if (ft_strequ(cmd[2 + punctuation], "-ne"))
		return (ft_test_ne(cmd));
	else if (ft_strequ(cmd[2 + punctuation], "-ge"))
		return (ft_test_ge(cmd));
	else if (ft_strequ(cmd[2 + punctuation], "-gt"))
		return (ft_test_gt(cmd));
	else if (ft_strequ(cmd[2 + punctuation], "-lt"))
		return (ft_test_lt(cmd));
	else if (ft_strequ(cmd[2 + punctuation], "-le"))
		return (ft_test_le(cmd));
	else if (ft_strequ(cmd[2 + punctuation], "="))
		return (ft_test_equal(cmd));
	return (-1);
}

//	-b, -c, -d, -e, -f, -g, -L, -p, -r, -S, -s, -u, -w, -x, -z, !
static int	operator_dispatcher(char **cmd, int punctuation)
{
	if (ft_strequ(cmd[1 + punctuation], "-b"))
		return (ft_test_b(cmd));
	else if (ft_strequ(cmd[1 + punctuation], "-c"))
		return (ft_test_c(cmd));
	else if (ft_strequ(cmd[1 + punctuation], "-d"))
		return (ft_test_d(cmd));
	else if (ft_strequ(cmd[1 + punctuation], "-e"))
		return (ft_test_e(cmd));
	else if (ft_strequ(cmd[1 + punctuation], "-f"))
		return (ft_test_f(cmd));
	else if (ft_strequ(cmd[1 + punctuation], "-g"))
		return (ft_test_g(cmd));
	else if (ft_strequ(cmd[1 + punctuation], "-L"))
		return (ft_test_capital_l(cmd));
	else if (ft_strequ(cmd[1 + punctuation], "-p"))
		return (ft_test_p(cmd));
	else if (ft_strequ(cmd[1 + punctuation], "-r"))
		return (ft_test_r(cmd));
	else if (ft_strequ(cmd[1 + punctuation], "-S"))
		return (ft_test_capital_s(cmd));
	else if (ft_strequ(cmd[1 + punctuation], "-s"))
		return (ft_test_s(cmd));
	else
		return (operator_dispatcher_continue(cmd, punctuation));
}

int	ft_test(t_shell *sh, char **cmd)
{
	int		punctuation;

	punctuation = 0;
	if (cmd[1] && ft_strequ(cmd[1], "!"))
		punctuation = 1;
	sh->exit_stat = 1;
	if (validate_input(sh, cmd, punctuation))
		return (0);
	sh->exit_stat = operator_dispatcher(cmd, punctuation);
	return (0);
}
