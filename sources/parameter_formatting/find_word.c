/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:26:17 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/11 11:20:28 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static char	*find_from_begin(char *haystack, char *needle)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	//ft_printf(" haystack [%s] needle [%s] [%d]\n", &haystack[i], &needle[j], j);
	while (haystack[i] == needle[j])
	{
		//ft_printf(" haystack [%s] needle [%s] [%d]\n", &haystack[i], &needle[j], j);
		i++;
		j++;
		if (!haystack[i])
		{
			return (NULL);
		}
		if (!needle[j])
		{
			//ft_printf(" haystack [%s] \n", &haystack[i]);
			return (&haystack[i]);
		}
	}
	return (haystack);
}

static char	*find_from_begin_last(char *haystack, char *needle)
{
	int	len;
	int	len_needle;
	int	k;
	int	i;

	len = (int)ft_strlen(haystack) - 1;
	k = 0;
	i = 0;
//	ft_printf("haystack [%s] needle [%s]\n", haystack, needle);
	while (len > 0)
	{
		len_needle = (int)ft_strlen(needle) - 1;
		//ft_printf("haystack [%c] needle [%c]\n", haystack[len], needle[len_needle]);
		while (haystack[len] == needle[len_needle])
		{
			//ft_printf("haystack [%s] needle [%s] %d\n", &haystack[len], &needle[len_needle], len_needle);
			//ft_printf(" haystack [%s] needle [%s] [%d]\n", &haystack[*i], &needle[*j], j);
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
	int	len;
	int	len_needle;
	int	k;
	int	i;
	char	*temp;

	len = (int)ft_strlen(haystack) - 1;
	k = 0;
	i = 0;
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
	int	i;
	int	j;
	char *temp;

	i = 0;
	while (haystack[i])
	{
		j = 0;
		while (haystack[i] == needle[j])
		{
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

	remove_globstars(&needle, &glob);
	if (*haystack)
	{
		//ft_printf("haystack %sglob %d needle %s %s\n",haystack, glob, needle, op);
		if (glob && ft_strequ("#", op))
			return (find_from_begin_glob(haystack, needle));
		else if ((!glob && ft_strequ("#", op))
			|| (!glob && ft_strequ("##", op)))
			return (find_from_begin(haystack, needle));
		else if (glob && ft_strequ("##", op))
			return (find_from_begin_last(haystack, needle));
		else if ((!glob && ft_strequ("%", op))
			|| (!glob && ft_strequ("%%", op)))
			return (find_from_end(haystack, needle));
		else if ((glob && ft_strequ("%", op)))
			return (find_from_first_last(haystack, needle));
		else if ((glob && ft_strequ("%%", op)))
			return (find_from_end_last(haystack, needle));
		else
			return (find_from_begin(haystack, needle));
	}
	return (haystack);
}
