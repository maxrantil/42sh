/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_globstars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:33:53 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/21 15:05:16 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	check_globs(char **needle, int *glob, char op)
{
	if (**needle == '*' && op != '%')
		*glob = 1;
	else if ((*needle)[ft_strlen(*needle) - 1] == '*' && op == '%')
		*glob = 1;
	else if ((*needle)[ft_strlen(*needle) - 1] == '*' && op != '%')
		*glob = 2;
	else if (**needle == '*' && op == '%')
		*glob = 2;
}

char	*remove_globstars(char **needle, int *glob, char op)
{
	char	*new_needle;
	char	*temp;
	int		len;

	*glob = 0;
	temp = ft_strchr(*needle, '*');
	len = ft_strlen(*needle);
	check_globs(needle, glob, op);
	if (*glob == 1 && op != '%')
	{
		(*needle)++;
		new_needle = ft_strdup(*needle);
	}
	else if ((*glob == 2 && op != '%') || (*glob == 1 && op == '%'))
		new_needle = ft_strndup(*needle, ft_strlen(*needle) - 1);
	else if (temp)
		new_needle = ft_strndup(*needle, ft_strlen(*needle) - ft_strlen(temp));
	else
		new_needle = ft_strdup(*needle);
	return (new_needle);
}
