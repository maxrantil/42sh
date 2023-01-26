/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:42:17 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/26 09:55:24 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	free_tokens(t_token **tokens)
{
	int	i;

	i = -1;
	while (*tokens && (*tokens)[++i].token)
	{
		if ((*tokens)[i].value)
			ft_strdel(&(*tokens)[i].value);
		(*tokens)[i].token = 0;
	}
	if (*tokens)
		ft_memdel((void **)tokens);
}
