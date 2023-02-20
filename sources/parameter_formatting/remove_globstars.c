/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_globstars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:33:53 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/20 21:44:40 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static char *glob_percent(char ***needle, int *glob)
{
	int		len;
	int		temp_len;
	char	*new_needle;
	char	*temp;

	len = ft_strlen(**needle);
	temp_len = len;
	temp = ft_strrchr(**needle, '*');
	ft_printf("temp %s %d\n", temp, temp_len);
	if (temp)
	{
		ft_printf("temp start%s\n", temp);
		temp++;
		*glob = 1;
	}
	if (*temp)
	{
		ft_printf("temp %s\n", temp);
		new_needle = ft_strdup(temp);
		temp_len = ft_strlen(temp);
		ft_printf("temp_len %d\n", temp_len);
		//ft_printf("new_needle %s\n", temp);
	}
	else if (*glob)
	{
		len--;
		ft_printf("juu %s\n", **needle);
		(**needle)[len] = '\0';
		ft_printf("juu %s\n", **needle);
		new_needle = ft_strdup(**needle);
	}
	else if (temp)
		new_needle = ft_strndup(**needle, ft_strlen(**needle) - ft_strlen(temp));
	else 
		new_needle = ft_strdup(**needle);
	while (temp_len >= 0)
	{
		ft_printf("juu %d\n", temp_len);
		(**needle)[len--] = '\0';
		temp_len--;
		ft_printf("no tassa %s\n", **needle);
	}
	return (new_needle);
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
	if  (*glob)
	{
		(*needle)++;
		new_needle = ft_strdup(*needle);
	}
	else if (temp)
		new_needle = ft_strndup(*needle, ft_strlen(*needle) - ft_strlen(temp));
	else 
		new_needle = ft_strdup(*needle);
	while(**needle && **needle != '*')
		(*needle)++;
	return (new_needle);
}
