/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_globstars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:33:53 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/21 12:01:10 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

// static void	get_new_needle_percent(t_perc *perc, char ****needle, int *glob)
// {
// 	if (perc->temp && *perc->temp)
// 	{
// 		perc->new_needle = ft_strdup(perc->temp);
// 		perc->temp_len = ft_strlen(perc->temp);
// 	}
// 	else if (*glob)
// 	{
// 		perc->len--;
// 		(***needle)[perc->len] = '\0';
// 		perc->new_needle = ft_strdup(***needle);
// 	}
// 	else if (perc->temp)
// 		perc->new_needle = \
// 		ft_strndup(***needle, ft_strlen(***needle) - ft_strlen(perc->temp));
// 	else
// 		perc->new_needle = ft_strdup(***needle);
// }

// static void	init_perc(t_perc *perc, char ***needle)
// {
// 	perc->len = ft_strlen(**needle);
// 	perc->temp_len = perc->len;
// 	perc->temp = ft_strrchr(**needle, '*');
// }

// static char	*glob_percent(char ***needle, int *glob)
// {
// 	t_perc	perc;

// 	init_perc(&perc, needle);
// 	if (perc.temp)
// 	{
// 		perc.temp++;
// 		*glob = 1;
// 	}
// 	get_new_needle_percent(&perc, &needle, glob);
// 	while (perc.temp_len >= 0)
// 	{
// 		(**needle)[perc.len--] = '\0';
// 		perc.temp_len--;
// 	}
// 	return (perc.new_needle);
// }

char	*remove_globstars(char **needle, int *glob, char op)
{
	char	*new_needle;
	char	*temp;
	int		len;

	*glob = 0;
	temp = ft_strchr(*needle, '*');
	len = ft_strlen(*needle);
	if (**needle == '*' && op != '%')
		*glob = 1;
	else if ((*needle)[ft_strlen(*needle) - 1] == '*' && op == '%')
		*glob = 1;
	else if ((*needle)[ft_strlen(*needle) - 1] == '*' && op != '%')
		*glob = 2;
	else if (**needle == '*' && op == '%')
		*glob = 2;
	if (*glob == 1 && op != '%')
	{
		(*needle)++;
		new_needle = ft_strdup(*needle);
	}
	else if ((*glob == 2 && op != '%') || (*glob == 1 && op == '%'))
	{
		new_needle = ft_strndup(*needle, ft_strlen(*needle) - 1);
	}
	else if (temp)
		new_needle = ft_strndup(*needle, ft_strlen(*needle) - ft_strlen(temp));
	else
		new_needle = ft_strdup(*needle);
	ft_printf("needle %s\n", new_needle);
	return (new_needle);
}
