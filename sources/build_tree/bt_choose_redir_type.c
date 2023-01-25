/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_redir_type.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:19:44 by jniemine          #+#    #+#             */
/*   Updated: 2022/12/14 15:25:42 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	choose_redir_type(t_token *tokens, t_treenode **redir, int i_tok, int cmd)
{
	if (tokens[i_tok].token == CLOSEFD)
		return (if_closefd(tokens, redir, i_tok, cmd));
	if (tokens[i_tok].token == AGGREGATION)
		return (if_aggregation(tokens, redir, i_tok, cmd));
	if (tokens[i_tok].token == REDIR)
		return (if_redir(tokens, redir, i_tok, cmd));
	return (0);
}
