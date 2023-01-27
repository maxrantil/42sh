/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_error_after_tokenizing.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakken <jakken@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:26:19 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/27 11:07:08 by jakken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	op(int token)
{
	return (token == PIPE || token == SEMICOLON
		|| token == LOGICAL_AND || token == LOGICAL_OR
		|| token == AMPERSAND);
}

//Maybe make printing more pretty with `<op>'
int	validate_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].token)
	{
		if (tokens[i + 1].token && op(tokens[i].token)
			&& (op(tokens[i + 1].token)))
		{
			ft_err_print(NULL, "syntax error near unexpected token",
				tokens[i + 1].value, 1);
			return (1);
		}
		++i;
	}
	return (0);
}
