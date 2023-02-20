/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retokenize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:49:04 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/20 15:40:38 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	is_dollar(char *fresh, char *trimmed, int *i, int *open)
{
	if (fresh[0] == '$')
	{
		if (trimmed[*i] == '{')
			*open += 1;
	}
}

static int	is_curly_end(char *fresh, char *trimmed, int *i, int *open, int k)
{
	if (trimmed[*i] == '}')
	{
		*open -= 1;
		if (*open == 0)
		{
			fresh[k++] = trimmed[(*i)++];
			return (1);
		}
	}
	return (0);
}

char	*retokenize(char *subst, int *i)
{
	int		k;
	int		open;
	char	*fresh;

	k = 0;
	open = 0;
	if (!subst)
		return (NULL);
	fresh = ft_strnew(ft_strlen(subst));
	while (subst[*i])
	{
		fresh[k++] = subst[(*i)++];
		is_dollar(fresh, subst, i, &open);
		if (is_curly_end(fresh, subst, i, &open, k))
			break ;
		if (subst[*i] == '$' && !open && subst[*i - 1] != '\'' && subst[*i - 1] != '\\')
			break ;
	}
	return (fresh);
}
