/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 23:10:34 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/24 15:16:40 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static char	*find_from_begin(char *haystack, char *needle, int glob)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!haystack[i] || (glob == 2 && !*needle))
		return (ft_strnew(1));
	while (haystack[i] == needle[j])
	{
		i++;
		j++;
		if (!haystack[i] && needle[j])
			return (ft_strdup(haystack));
		if (!needle[j])
		{
			if (glob == 2)
				return (ft_strnew(1));
			return (ft_strdup(&haystack[i]));
		}
	}
	return (ft_strdup(haystack));
}

static char	*find_from_begin_last(char *haystack, char *needle)
{
	int	len;
	int	len_needle;

	len = (int)ft_strlen(haystack) - 1;
	if (!*haystack || !*needle)
		return (ft_strnew(1));
	while (len > 0)
	{
		len_needle = (int)ft_strlen(needle) - 1;
		while (haystack[len] == needle[len_needle])
		{
			len--;
			len_needle--;
			if (len < 0 && len_needle > 0)
				return (ft_strnew(1));
			if (len_needle < 0)
				return (ft_strdup(&haystack[len + (int)ft_strlen(needle) + 1]));
		}
		len--;
	}
	return (haystack);
}

static char	*find_from_first_last(char *haystack, char *needle)
{
	int	hay_len;
	int	needle_len;
	int	i;
	int	j;

	hay_len = (int)ft_strlen(haystack);
	needle_len = (int)ft_strlen(needle);
	i = hay_len - 1;
	j = needle_len - 1;
	while (i >= 0)
	{
		if (haystack[i] == needle[j])
		{
			j--;
			if (j < 0)
				return (ft_strndup(haystack, i));
		}
		else
			j = needle_len - 1;
		i--;
	}
	return (ft_strdup(haystack));
}

static char	*find_from_end_last(char *haystack, char *needle)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	if (!haystack[i] || !*needle)
		return (ft_strnew(1));
	while (haystack[i])
	{
		j = 0;
		while (haystack[i] == needle[j])
		{
			i++;
			j++;
			if (!haystack[i] && needle[j])
				return (ft_strnew(1));
			if (!needle[j])
			{
				temp = ft_strndup(haystack, i - ft_strlen(needle));
				return (temp);
			}
		}
		i++;
	}
	return (ft_strdup(haystack));
}

char	*get_word(char *temp, char *temp_needle, char *op, int glob)
{
	if (!glob && !*temp_needle)
		temp = ft_strdup(temp);
	if (glob == 1 && ft_strequ("#", op))
		temp = find_from_begin_glob(temp, temp_needle);
	else if ((glob == 2 && ft_strequ("#", op))
		|| (!glob && ft_strequ("#", op)))
		temp = find_from_begin(temp, temp_needle, 0);
	else if ((glob == 2 && ft_strequ("##", op))
		|| (!glob && ft_strequ("##", op)))
		temp = find_from_begin(temp, temp_needle, glob);
	else if (glob == 1 && ft_strequ("##", op))
		temp = find_from_begin_last(temp, temp_needle);
	else if ((!glob && ft_strequ("%", op)))
		temp = find_from_end(temp, temp_needle, 0);
	else if (glob && ft_strequ("%", op))
		temp = find_from_first_last(temp, temp_needle);
	else if (glob == 1 && ft_strequ("%%", op))
		temp = find_from_end_last(temp, temp_needle);
	else if ((!glob && ft_strequ("%%", op))
		|| (glob == 2 && ft_strequ("%%", op)))
		temp = find_from_end(temp, temp_needle, glob);
	return (temp);
}
