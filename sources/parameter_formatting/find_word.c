/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:26:17 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/20 23:29:21 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

char	*ft_find_word(char **haystack, char *needle, char *op)
{
	int		glob;
	char	*temp;
	char	*temp_needle;

	glob = 1;
	temp = *haystack;
	while (*needle)
	{
		if (!temp)
			break ;
		glob = 0;
		temp_needle = remove_globstars(&needle, &glob, *op);
		temp = get_word(temp, temp_needle, op, glob);
		ft_strdel(&temp_needle);
		if (ft_strequ(temp, *haystack))
			break ;
	}
	return (temp);
}
