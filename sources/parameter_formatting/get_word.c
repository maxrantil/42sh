/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 23:10:34 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/21 13:51:44 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static char	*find_from_begin(char *haystack, char *needle)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (haystack[i] == needle[j])
	{
		i++;
		j++;
		if (!haystack[i] && needle[j])
			return (NULL);
		if (!needle[j])
			return (ft_strdup(&haystack[i]));
	}
	return (ft_strdup(haystack));
}

static char	*find_from_begin_last(char *haystack, char *needle)
{
	int	len;
	int	len_needle;

	len = (int)ft_strlen(haystack) - 1;
	if (!*needle)
		return (NULL);
	while (len > 0)
	{
		len_needle = (int)ft_strlen(needle) - 1;
		while (haystack[len] == needle[len_needle])
		{
			len--;
			len_needle--;
			if (len < 0 && len_needle > 0)
			{
				return (NULL);
			}
			if (len_needle < 0)
				return (ft_strdup(&haystack[len + (int)ft_strlen(needle) + 1]));
		}
		len--;
	}
	return (haystack);
}

static char	*find_from_first_last(char *haystack, char *needle)
{
	int		len;
	int		len_needle;
	char	*temp;

	len = (int)ft_strlen(haystack);
	while (--len > 0)
	{
		if (haystack[len] == needle[len_needle])
		{
			len_needle--;
			if (len < 0 && len_needle > 0)
				return (NULL);
			if (len_needle < 0)
			{
				temp = ft_strndup(haystack, len);
				return (temp);
			}
			else
				len_needle = (int)ft_strlen(needle) - 1;
		}
	}
	return (ft_strdup(haystack));
}

static char	*find_from_end_last(char *haystack, char *needle)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	if (!*needle)
		return (NULL);
	while (haystack[i])
	{
		j = 0;
		while (haystack[i] == needle[j])
		{
			i++;
			j++;
			if (!haystack[i] && needle[j])
				return (ft_strdup(haystack));
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
	if (glob && ft_strequ("#", op))
		temp = find_from_begin_glob(temp, temp_needle);
	else if ((!glob && ft_strequ("#", op))
		|| (!glob && ft_strequ("##", op)))
		temp = find_from_begin(temp, temp_needle);
	else if (glob == 1 && ft_strequ("##", op))
		temp = find_from_begin_last(temp, temp_needle);
	else if ((!glob && ft_strequ("%", op))
		|| (!glob && ft_strequ("%%", op)))
		temp = find_from_end(temp, temp_needle);
	else if ((glob == 1 && ft_strequ("%", op)))
		temp = (find_from_first_last(temp, temp_needle));
	else if ((glob == 1 && ft_strequ("%%", op))
		|| (glob == 2 && ft_strequ("##", op)))
		temp = find_from_end_last(temp, temp_needle);
	else
		temp = find_from_begin(temp, temp_needle);
	return (temp);
}
