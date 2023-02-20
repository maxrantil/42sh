/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_globstars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:33:53 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/20 23:17:32 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	get_new_needle_percent(t_perc *perc, char ****needle, int *glob)
{
	if (perc->temp && *perc->temp)
	{
		perc->new_needle = ft_strdup(perc->temp);
		perc->temp_len = ft_strlen(perc->temp);
	}
	else if (*glob)
	{
		perc->len--;
		(***needle)[perc->len] = '\0';
		perc->new_needle = ft_strdup(***needle);
	}
	else if (perc->temp)
		perc->new_needle = \
		ft_strndup(***needle, ft_strlen(***needle) - ft_strlen(perc->temp));
	else
		perc->new_needle = ft_strdup(***needle);
}

static void	init_perc(t_perc *perc, char ***needle)
{
	perc->len = ft_strlen(**needle);
	perc->temp_len = perc->len;
	perc->temp = ft_strrchr(**needle, '*');
}

static char	*glob_percent(char ***needle, int *glob)
{
	t_perc	perc;

	init_perc(&perc, needle);
	if (perc.temp)
	{
		perc.temp++;
		*glob = 1;
	}
	get_new_needle_percent(&perc, &needle, glob);
	while (perc.temp_len >= 0)
	{
		(**needle)[perc.len--] = '\0';
		perc.temp_len--;
	}
	return (perc.new_needle);
}

char	*remove_globstars(char **needle, int *glob, char op)
{
	char	*new_needle;
	char	*temp;

	*glob = 0;
	temp = ft_strchr(*needle, '*');
	if (op == '%')
	{
		new_needle = glob_percent(&needle, glob);
		return (new_needle);
	}
	if (**needle == '*')
		*glob = 1;
	if (*glob)
	{
		(*needle)++;
		new_needle = ft_strdup(*needle);
	}
	else if (temp)
		new_needle = ft_strndup(*needle, ft_strlen(*needle) - ft_strlen(temp));
	else
		new_needle = ft_strdup(*needle);
	while (**needle && **needle != '*')
		(*needle)++;
	return (new_needle);
}
