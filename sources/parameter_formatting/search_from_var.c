/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_from_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:38:39 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/02 13:47:28 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

// static char	*remove_braces(char *str)
// {
// 	char	*new;
// 	int		i;
// 	int		k;

// 	k = 0;
// 	i = 1;
// 	str[1] = str[2];
// 	str[ft_strlen(str) - 1] = '\0';
// 	ft_printf("%s\n", str);
// 	while (str[i])
// 	{
// 		str[i] = str[i + 1];
// 		i++;
// 	}
// 	ft_printf("%s\n", str);
// 	new = ft_strdup(str);
// 	return (new);
// }

// char *go_to_haystack(char *haystack, char *needle)
// {
// 	int		i;
// 	int		k;
// 	char	*fresh;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	while (haystack[i])
// 	{
// 		while(haystack[i] == needle[k])
// 			fresh[j++]
// 	}
// }

static char	*find_from_begin_glob(int *i, int *j, char *haystack, char *needle)
{
	ft_printf(" haystack [%s] needle [%s] [%d]\n", &haystack[*i], &needle[*j], j);
	while (haystack[*i] == needle[*j])
	{
		ft_printf(" haystack [%s] needle [%s] [%d]\n", &haystack[*i], &needle[*j], j);
		(*i)++;
		(*j)++;
		if (!haystack[*i])
		{
			return (NULL);
		}
		if (!needle[*j])
		{
			ft_printf(" haystack [%s] \n", &haystack[*i]);
			return (&haystack[*i]);
		}
	}
	return (haystack);
}

static char	*find_from_begin(int *i, int *j, char *haystack, char *needle)
{
	ft_printf(" haystack [%s] needle [%s] [%d]\n", &haystack[*i], &needle[*j], j);
	while (haystack[*i] == needle[*j])
	{
		ft_printf(" haystack [%s] needle [%s] [%d]\n", &haystack[*i], &needle[*j], j);
		(*i)++;
		(*j)++;
		if (!haystack[*i])
		{
			return (NULL);
		}
		if (!needle[*j])
		{
			ft_printf(" haystack [%s] \n", &haystack[*i]);
			return (&haystack[*i]);
		}
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
	ft_printf("fl;gsdfl;kjsgd needle %c\n", (*needle)[len - 1]);
	while ((*needle)[len - 1] == '*')
	{
		(*needle)[len - 1] = '\0';
		len--;
	}
}

char	*ft_find_word(char *haystack, char *needle)
{
	int		i;
	int		j;
	int		glob;

	i = 0;
	remove_globstars(&needle, &glob);
	while (haystack[i])
	{
		j = 0;
		ft_printf("%d %s\n", glob, needle);
		if (glob)
			haystack = find_from_begin_glob(&i, &j, haystack, needle);
		else
			return (find_from_begin(&i, &j, haystack, needle));
		if (haystack[i])
			i++;
	}
	return (haystack);
}

static char	*remove_braces(char *str)
{
	char	*new;
	int		i;
	int		k;

	k = 0;
	i = 1;
	ft_printf("%c\n", str[1]);
	if (!str[1] || str[1] != '{')
		return (str);
	str[1] = str[2];
	str[ft_strlen(str) - 1] = '\0';
	ft_printf("%s\n", str);
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
	ft_printf("%s\n", str);
	new = ft_strdup(str);
	return (new);
}

char	*search_from_var(t_shell *sh, char *cmd, int *ret)
{
	char	*expanded;
	char	*needle;
	char	*haystack;
	char	*splitted;
	char	*strip;

	strip = remove_braces(cmd);
	if (ft_strchr(cmd, '#'))
	{
		needle = ft_strdup(ft_strchr(strip, '#'));
		needle = ft_memmove(needle, needle + 1, ft_strlen(needle));
	}
	else if (ft_strchr(strip, '%'))
		needle = ft_strdup(ft_strchr(strip, '%'));
	else
		needle = NULL;
	if (needle == NULL)
		exit(1);
	haystack = ft_strndup(strip, ft_strlen(strip) - ft_strlen(needle) - 1);
	haystack = ft_expansion_dollar(sh, &haystack[0]);
	(void)sh;
	(void)*ret;
	ft_printf(" needle [%s] haystack [%s]\n", needle, haystack);
	expanded = ft_find_word(haystack, needle);
	if (!expanded || !*expanded)
		expanded = ft_strdup(" ");
	ft_printf("search expanded %s\n", expanded);
	expanded = ft_strdup(expanded);
	ft_strdel(&needle);
	ft_strdel(&haystack);
	return (expanded);
}
