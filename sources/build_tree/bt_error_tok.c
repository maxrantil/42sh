/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_error_tok.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:32:10 by jniemine          #+#    #+#             */
/*   Updated: 2022/12/19 16:10:34 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	error_tok(t_treenode *redir_head, char *msg, char *symbol)
{
	if (!symbol && msg)
		ft_err_print(NULL, NULL, msg, 2);
	else if (symbol && msg)
		ft_err_print(NULL, msg, symbol, 2);
	free_node(redir_head);
	return (1);
}
