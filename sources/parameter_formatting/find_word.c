/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:26:17 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/21 13:39:00 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

char	*ft_find_word(char *haystack, char *needle, char *op)
{
	int		glob;
	char	*temp;
	char	*temp_needle;

	glob = 1;
	temp = haystack;
	if (haystack)
	{
		glob = 0;
		temp_needle = remove_globstars(&needle, &glob, *op);
		temp = get_word(temp, temp_needle, op, glob);
		ft_printf("temp [%p]\n", temp);
		ft_strdel(&temp_needle);
		ft_printf("temp [%s] haystack [%s]\n", temp ,haystack);
	}
	return (temp);
}
