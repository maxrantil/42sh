/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_globstars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:33:53 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/23 09:18:29 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	check_globs(char **needle, int *glob, char op)
{
	if (**needle == '*' && op != '%')
		*glob = 1;
	if ((*needle)[ft_strlen(*needle) - 1] == '*' && op != '%')
		*glob += 2;
	if ((*needle)[ft_strlen(*needle) - 1] == '*' && op == '%')
		*glob = 1;
	if (**needle == '*' && op == '%')
		*glob += 2;
}

char	*remove_globstars(char **needle, int *glob, char op)
{
	char	*new_needle;
	int		len;

	*glob = 0;
	new_needle = NULL;
	len = ft_strlen(*needle);
	check_globs(needle, glob, op);
	if ((*glob == 1 && op != '%') || (*glob == 2 && op == '%'))
		new_needle = strdup(*needle + 1);
	else if ((*glob == 2 && op != '%') || (*glob == 1 && op == '%'))
		new_needle = strndup(*needle, len - 1);
	else if (*glob == 3)
	{
		ft_printf("glob %d\n", *glob);
		new_needle = strndup(*needle + 1, len - 2);
		*glob = 2;
		ft_printf("glob %dneedle %s\n", *glob, new_needle);
	}
	else
		new_needle = strdup(*needle);
	return (new_needle);
}
