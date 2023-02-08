/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_from_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:38:39 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/08 14:38:19 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static char	*find_from_begin_glob(char *haystack, char *needle)
{
	int	i;
	int	j;

	i = 0;
	while (haystack[i])
	{
		j = 0;
		while (haystack[i] == needle[j])
		{
			i++;
			j++;
			if (!haystack[i])
			{
				return (haystack);
			}
			if (!needle[j])
			{
				ft_printf(" haystack [%s] \n", &haystack[i]);
				return (&haystack[i]);
			}
		}
		i++;
	}
	return (haystack);
}

static char	*find_from_end(char *haystack, char *needle)
{
	int	len;
	int	len_needle;
	int	k;
	int	i;

	len = (int)ft_strlen(haystack);
	k = 0;
	i = 0;
	ft_printf("haystack %s len [%d]]\n",haystack, len);
	while (len > 0)
	{
		len_needle = (int)ft_strlen(needle);
		while (haystack[len] == needle[len_needle])
		{
			len--;
			len_needle--;
			if (len == 0)
			{
				return (NULL);
			}
			if (len_needle == 0)
			{
				ft_printf(" haystack [%s] \n", &haystack[len]);
				haystack = ft_strndup(haystack, ft_strlen(haystack) - ft_strlen(needle) + 1);
				return (haystack);
			}
		}
		len--;
	}
	return (haystack);
}

static char	*find_from_begin(char *haystack, char *needle)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ft_printf(" haystack [%s] needle [%s] [%d]\n", &haystack[i], &needle[j], j);
	while (haystack[i] == needle[j])
	{
		ft_printf(" haystack [%s] needle [%s] [%d]\n", &haystack[i], &needle[j], j);
		i++;
		j++;
		if (!haystack[i])
		{
			return (NULL);
		}
		if (!needle[j])
		{
			ft_printf(" haystack [%s] \n", &haystack[i]);
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
	ft_printf("haystack [%s] needle [%s]\n", haystack, needle);
	while (len > 0)
	{
		len_needle = (int)ft_strlen(needle) - 1;
		//ft_printf("haystack [%c] needle [%c]\n", haystack[len], needle[len_needle]);
		while (haystack[len] == needle[len_needle])
		{
			ft_printf("haystack [%s] needle [%s] %d\n", &haystack[len], &needle[len_needle], len_needle);
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
	ft_printf("haystack [%s] needle [%s]\n", haystack, needle);
	while (len > 0)
	{
		len_needle = (int)ft_strlen(needle) - 1;
		//ft_printf("haystack [%c] needle [%c]\n", haystack[len], needle[len_needle]);
		while (haystack[len] == needle[len_needle])
		{
			ft_printf("haystack [%s] needle [%s] %d\n", &haystack[len], &needle[len_needle], len_needle);
			//ft_printf(" haystack [%s] needle [%s] [%d]\n", &haystack[*i], &needle[*j], j);
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
		ft_printf(" haystack [%s] needle [%s] [%d]\n", &haystack[i], &needle[j], j);
		while (haystack[i] == needle[j])
		{
			i++;
			j++;
			if (!haystack[i])
			{
				return (haystack);
			}
			if (!needle[j])
			{
				ft_printf(" haystack [%s] \n", &haystack[i]);
				temp = ft_strndup(haystack, i - ft_strlen(needle));
				ft_printf(" temp [%s] \n", temp);
				return (temp);
			}
		}
		i++;
	}
	return (haystack);
}

void	remove_globstars(char **needle, int *glob)
{
	int	len;

	*glob = 0;
	len = ft_strlen(*needle);
	while (**needle == '*')
	{
		*glob = 1;
		(*needle)++;
	}
	while ((*needle)[len - 1] == '*')
	{
		*glob = 3;
		(*needle)[len - 1] = '\0';
		len--;
	}
}

char	*ft_find_word(char *haystack, char *needle, char *op)
{
	int		glob;

	remove_globstars(&needle, &glob);
	if (*haystack)
	{
		ft_printf("haystack %sglob %d needle %s %s\n",haystack, glob, needle, op);
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


char *get_needle_and_op(char *strip, char *op, char *cmd)
{
	char	*needle;
	int		k;

	k = -1;
	needle = NULL;
	ft_printf("cmd %s\n", cmd);
	if (ft_strchr(cmd, '#'))
	{
		needle = ft_strdup(ft_strchr(strip, '#'));
		while (needle[++k] == '#')
			op[k] = needle[k];
		needle = ft_memmove(needle, needle + 1 + (k - 1), ft_strlen(needle));
	}
	else if (ft_strchr(strip, '%'))
	{
		needle = ft_strdup(ft_strchr(strip, '%'));
		while (needle[++k] == '%')
			op[k] = needle[k];
		needle = ft_memmove(needle, needle + 1 + (k - 1), ft_strlen(needle));
	}
	return (needle);
}

char	*search_from_var(t_shell *sh, char *cmd, int *ret)
{
	char	*expanded;
	char	*needle;
	char	*haystack;
	char	op[3];
	char	*strip;
	char	*temp;
	char	*temp2;

	strip = ft_strdup(cmd);
	strip = remove_braces(strip);
	temp = NULL;
	ft_memset(&op, '\0', 3);
	needle = get_needle_and_op(strip, op, cmd);
	if (!*needle)
		return NULL;
	ft_printf(" needle [%s] \n", needle);
	if ((ft_strnequ(needle, "${", 2) && ft_strchr(needle , '#'))
		|| (ft_strnequ(needle, "${", 2) && ft_strchr(needle , '%')))
		temp = search_from_var(sh, needle, ret);
	else if (ft_strnequ(needle, "${", 2))
		temp = substitute_or_create(sh, needle, ret);
	else //if (needle[0] == '$')//if (ft_strnequ(needle, "${", 2))
		temp = ft_expansion_dollar(sh, needle);
	temp2 = ft_strndup(strip, ft_strlen(strip) - ft_strlen(needle) - ft_strlen(op));
	haystack = ft_expansion_dollar(sh, temp2);
	ft_printf(" temp [%s] haystack [%s] [%s]\n", temp, haystack, op);
	if (temp != NULL)
	{
		ft_strdel(&needle);
		needle = ft_strdup(temp);
		ft_printf(" needle [%s] \n", needle);
		ft_strdel(&temp);
	}
	(void)sh;
	(void)*ret;
	expanded = ft_strdup(ft_find_word(haystack, needle, op));
	ft_printf("expanded last [%s] \n", expanded);
	if (!expanded || !*expanded)
		expanded = ft_strnew(1);
	ft_strdel(&needle);
	ft_strdel(&strip);
	ft_strdel(&haystack);
	ft_strdel(&temp2);
	return (expanded);
}
