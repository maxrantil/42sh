/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_from_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:38:39 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/21 13:43:43 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static char	*get_needle_and_op(char *strip, char *op, char *cmd)
{
	char	*needle;
	int		k;

	k = -1;
	needle = NULL;
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

static int	is_expansion_id(char *needle)
{
	return (ft_strnequ(needle, "${", 2));
}

static void	replace_haystack(t_sub *sub, t_shell *sh)
{
	sub->temp_hays = ft_strndup(sub->strip, ft_strlen(sub->strip) \
		- ft_strlen(sub->needle) - ft_strlen(sub->op));
	sub->haystack = ft_expansion_dollar(sh, sub->temp_hays);
}

static void	expansion_subst(t_sub *sub, t_shell *sh, int *ret)
{
	if (is_substring_id(sub->needle))
		sub->temp_sub = search_from_var(sh, sub->needle, ret);
	else if (is_expansion_id(sub->needle))
		sub->temp_sub = substitute_or_create(sh, sub->needle, ret);
	else if (sub->needle[0] == '$')
		sub->temp_sub = ft_expansion_dollar(sh, sub->needle);
	else if (sub->needle[0] == '~')
		sub->temp_sub = ft_expansion_tilde(sh, sub->needle);
}

char	*search_from_var(t_shell *sh, char *cmd, int *ret)
{
	t_sub	sub;

	init_subs_session(&sub, cmd);
	sub.needle = get_needle_and_op(sub.strip, sub.op, cmd);
	expansion_subst(&sub, sh, ret);
	replace_haystack(&sub, sh);
	ft_quote_blash_removal(sub.haystack);
	if (!*sub.needle)
	{
		subs_session_free(&sub, 0);
		return (sub.haystack);
	}
	if (sub.temp_sub != NULL)
	{
		ft_strdel(&sub.needle);
		sub.needle = ft_strdup(sub.temp_sub);
		ft_strdel(&sub.temp_sub);
	}
	sub.expanded = ft_find_word(sub.haystack, sub.needle, sub.op);
	// if (!sub.expanded || !*sub.expanded)
	// {
	// 	ft_printf("here [%s]\n", sub.expanded);
	// 	// sub.expanded = ft_strnew(1);
	// }
	subs_session_free(&sub, 1);
	return (sub.expanded);
}
