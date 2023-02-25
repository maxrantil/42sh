/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_name.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 00:22:44 by jniemine          #+#    #+#             */
/*   Updated: 2023/02/25 00:32:55 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

char	**get_cmd_name(t_treenode *node)
{
	t_treenode	*head;

	head = (t_treenode *)node;
	while (head->type != CMD)
	{
		if ((head)->type == REDIR)
			head = (((t_redir *)(head))->cmd);
		else if ((head)->type == AGGREGATION)
			head = (((t_aggregate *)(head))->cmd);
		else if ((head)->type == CLOSEFD)
			head = (((t_closefd *)(head))->cmd);
	}
	return (((t_cmdnode *)head)->cmd);
}
