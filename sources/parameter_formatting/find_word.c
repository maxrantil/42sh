/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:26:17 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/20 21:08:02 by mviinika         ###   ########.fr       */
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
			return (&haystack[i]);
	}
	return (haystack);
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
				return (&haystack[len + (int)ft_strlen(needle) + 1]);
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

	len = (int)ft_strlen(haystack) - 1;
	while (len > 0)
	{
		len_needle = (int)ft_strlen(needle) - 1;
		while (haystack[len] == needle[len_needle])
		{
			len--;
			len_needle--;
			if (len < 0 && len_needle > 0)
				return (NULL);
			if (len_needle < 0)
			{
				temp = ft_strndup(haystack, len + 1);
				return (temp);
			}
		}
		len--;
	}
	return (haystack);
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
		ft_printf("haystack [%c]\n", haystack[i]);
		while (haystack[i] == needle[j])
		{
			ft_printf("haystack [%c] needle [%c]\n", haystack[i], needle[j]);
			i++;
			j++;
			if (!haystack[i] && needle[j])
				return (haystack);
			if (!needle[j])
			{
				temp = ft_strndup(haystack, i - ft_strlen(needle));
				return (temp);
			}
		}
		i++;
	}
	return (haystack);
}

char	*ft_find_word(char *haystack, char *needle, char *op)
{
	int		glob;
	char	*temp;
	char	*temp_needle;

	glob = 1;
	temp = haystack;
	while (*needle)
	{
		if (!temp)
			break;
		glob = 0;
		temp_needle = remove_globstars(&needle, &glob, *op);
		if (glob && ft_strequ("#", op))
			temp = find_from_begin_glob(temp , temp_needle);
		else if ((!glob && ft_strequ("#", op))
			|| (!glob && ft_strequ("##", op)))
			temp = find_from_begin(temp , temp_needle );
		else if (glob && ft_strequ("##", op))
			temp = find_from_begin_last(temp , temp_needle);
		else if ((!glob && ft_strequ("%", op))
			|| (!glob && ft_strequ("%%", op)))
			temp = find_from_end(temp , temp_needle );
		else if ((glob && ft_strequ("%", op)))
			temp = (find_from_first_last(temp , temp_needle));
		else if ((glob && ft_strequ("%%", op)))
			temp = find_from_end_last(temp , temp_needle);
		else
			temp = find_from_begin(temp ,temp_needle);
		ft_printf("temp [%s] needle [%s] op %s\n", temp, temp_needle, op);
		ft_strdel(&temp_needle);
		if (ft_strequ(temp, haystack))
			break ;

	}
	return (temp);
}
