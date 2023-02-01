/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_from_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:38:39 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/01 12:04:12 by mviinika         ###   ########.fr       */
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

char	*ft_find_word(char *haystac, char *needle)
{
	
}

char	*search_from_var(t_shell *sh, char *cmd, int *ret)
{
	char	*expanded;
	//char	*strip;
	char	*needle;
	char	*haystack;
	char	*splitted;

	// strip = ft_strdup(cmd);
	// remove_braces(strip);
	ft_printf(" needle [ aystack [%s\n", cmd);
	if (ft_strchr(cmd, '#'))
		needle = ft_strdup(ft_strchr(cmd, '#'));
	else if (ft_strchr(cmd, '%'))
		needle = ft_strdup(ft_strchr(cmd, '%'));
	else
		needle = NULL;
	haystack = ft_strndup(cmd, ft_strlen(cmd) - ft_strlen(needle));
	haystack = ft_expansion_dollar(sh, &haystack[0]);
	(void)sh;
	(void)*ret;
	ft_printf(" needle [%s] haystack [%s]\n", needle, haystack);
	expanded = ft_find_word(haystack, needle + 1);
	ft_printf("%s\n", expanded);
	exit(1);
	return 0;
}
