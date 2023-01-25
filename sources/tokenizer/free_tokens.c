/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:42:17 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/19 12:53:36 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

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
