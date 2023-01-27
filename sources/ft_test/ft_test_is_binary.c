/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_is_binary.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:31:13 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/26 15:45:32 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

// True if the strings s1 and s2 are identical.
int	ft_test_equal(char **arg)
{
	int		not;

	not = ft_test_is_not(arg);
	if (not && ft_strequ(arg[2], arg[4]))
		return (1);
	else if (ft_strequ(arg[1], arg[3]))
		return (0);
	return (ft_test_not_return_last(not));
}

//	True if the integer n1 is algebraically less than or equal
//	to the integer n2.
int	ft_test_le(char **arg)
{
	int		not;
	int		ret;

	not = ft_test_is_not(arg);
	ret = ft_test_check_int(arg, not);
	if (ret)
		return (ret);
	if (not && ft_atoi(arg[2]) <= ft_atoi(arg[4]))
		return (1);
	else if (ft_atoi(arg[1]) <= ft_atoi(arg[3]))
		return (0);
	return (ft_test_not_return_last(not));
}

//	True if the integer n1 is algebraically less than the
//	integer n2.
int	ft_test_lt(char **arg)
{
	int		not;
	int		ret;

	not = ft_test_is_not(arg);
	ret = ft_test_check_int(arg, not);
	if (ret)
		return (ret);
	not = ft_test_is_not(arg);
	if (not && ft_atoi(arg[2]) < ft_atoi(arg[4]))
		return (1);
	else if (ft_atoi(arg[1]) < ft_atoi(arg[3]))
		return (0);
	return (ft_test_not_return_last(not));
}

//	True if the integer n1 is algebraically greater than or equal
//	to the integer n2.
int	ft_test_ge(char **arg)
{
	int		not;
	int		ret;

	not = ft_test_is_not(arg);
	ret = ft_test_check_int(arg, not);
	if (ret)
		return (ret);
	not = ft_test_is_not(arg);
	if (not && ft_atoi(arg[2]) >= ft_atoi(arg[4]))
		return (1);
	else if (ft_atoi(arg[1]) >= ft_atoi(arg[3]))
		return (0);
	return (ft_test_not_return_last(not));
}

//	True if the integers n1 and n2 are not algebraically equal.
int	ft_test_ne(char **arg)
{
	int		not;
	int		ret;

	not = ft_test_is_not(arg);
	ret = ft_test_check_int(arg, not);
	if (ret)
		return (ret);
	not = ft_test_is_not(arg);
	if (not && ft_atoi(arg[2]) != ft_atoi(arg[4]))
		return (1);
	else if (ft_atoi(arg[1]) != ft_atoi(arg[3]))
		return (0);
	return (ft_test_not_return_last(not));
}

//	True if the integer n1 is algebraically equal to the integer n2.
int	ft_test_eq(char **arg)
{
	int		not;
	int		ret;

	not = ft_test_is_not(arg);
	ret = ft_test_check_int(arg, not);
	if (ret)
		return (ret);
	not = ft_test_is_not(arg);
	if (not && ft_atoi(arg[2]) == ft_atoi(arg[4]))
		return (1);
	else if (ft_atoi(arg[1]) == ft_atoi(arg[3]))
		return (0);
	return (ft_test_not_return_last(not));
}

// True if the strings s1 and s2 are not identical.
int	ft_test_not_equal(char **arg)
{
	int		not;
	int		ret;

	not = ft_test_is_not(arg);
	ret = ft_test_check_int(arg, not);
	if (ret)
		return (ret);
	not = ft_test_is_not(arg);
	if (not && !ft_strequ(arg[2], arg[4]))
		return (1);
	else if (!ft_strequ(arg[1], arg[3]))
		return (0);
	return (ft_test_not_return_last(not));
}

/*
	!=, -eq, -ne, -ge, -lt, -le, =
*/
int is_binary(char *str)
{
	return (ft_strequ(str, "!=") || ft_strequ(str, "-eq")
			|| ft_strequ(str, "-ne") || ft_strequ(str, "-ge")
			|| ft_strequ(str, "-lt") || ft_strequ(str, "-le")
			|| ft_strequ(str, "="));
}
