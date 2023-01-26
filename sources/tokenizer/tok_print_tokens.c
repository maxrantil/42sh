/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_print_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:28:50 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/26 09:55:24 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/* Call this in main after tokens have been created I guess */
void	print_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	ft_printf("------------------ TOKEN DEBUG ------------------\n");
	while (tokens[i].token)
	{
		ft_printf("TOKEN: [%d], VALUE: [%s]\n",
			tokens[i].token, tokens[i].value);
		++i;
	}
	ft_printf("------------------ TOKEN DEBUG ------------------\n");
}
