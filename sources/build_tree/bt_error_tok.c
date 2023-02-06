/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_error_tok.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:32:10 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/26 09:55:22 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int	error_tok(t_treenode *redir_head, char *msg, char *symbol)
{
	if (!symbol && msg)
		ft_err_print(NULL, NULL, msg, 2);
	else if (symbol && msg)
		ft_err_print(NULL, msg, symbol, 2);
	free_node(redir_head);
	return (1);
}
