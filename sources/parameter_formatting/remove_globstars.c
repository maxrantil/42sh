/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_globstars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:33:53 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/20 17:21:34 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

char	*remove_globstars(char **needle, int *glob)
{
	int		len;
	char	*new_needle;
	char	*temp;

	*glob = 0;
	temp = ft_strchr(*needle, '*');
	len = ft_strlen(*needle);
	if (len == 0)
		return (NULL);
	
	if (**needle == '*')
		*glob = 1;
	if  (*glob)
	{
		(*needle)++;
		ft_printf("old_needle %s\n", *needle);
		ft_printf("temp %s\n", *needle);
		new_needle = ft_strdup(*needle);
		ft_printf("new_needle %s\n", new_needle);
		//return (new_needle);
	}
	else if (temp)
		new_needle = ft_strndup(*needle, ft_strlen(*needle) - ft_strlen(temp));
	else 
		new_needle = ft_strdup(*needle);
	while(**needle && **needle != '*')
	{
		(*needle)++;
	}
	return (new_needle);
}
