/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retokenize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:49:04 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/21 09:25:13 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	is_dollar(t_retok *retok, char *trimmed, int *i)
{
	if (retok->fresh[0] == '$')
	{
		if (trimmed[*i] == '{')
			retok->open += 1;
	}
}

static int	is_curly_end(t_retok *retok, char *trimmed, int *i)
{
	if (trimmed[*i] == '}')
	{
		retok->open -= 1;
		if (retok->open == 0)
		{
			retok->fresh[retok->k++] = trimmed[(*i)++];
			return (1);
		}
	}
	return (0);
}

char	*retokenize(char *subst, int *i)
{
	t_retok	retok;

	retok.k = 0;
	retok.open = 0;
	if (!subst)
		return (NULL);
	retok.fresh = ft_strnew(ft_strlen(subst));
	while (subst[*i])
	{
		retok.fresh[retok.k++] = subst[(*i)++];
		is_dollar(&retok, subst, i);
		if (is_curly_end(&retok, subst, i))
			break ;
		if (subst[*i] == '$' && !retok.open && subst[*i - 1] != '\''
			&& subst[*i - 1] != '\\')
			break ;
	}
	return (retok.fresh);
}
