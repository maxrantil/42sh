/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:58:54 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/12 14:22:51 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	calculate_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].token)
		++i;
	return (i);
}

int	foreseer_of_tokens(t_token *tokens, int mark, int start, int end)
{
	if (!tokens)
		return (-1);
	while (tokens[start].token && start < end)
	{
		if (tokens[start].token == mark)
			return (start);
		++start;
	}
	return (-1);
}

int	get_close_fd(char *value)
{
	int		digit;
	char	*digits;
	int		res;

	digit = 0;
	digits = NULL;
	while (ft_isdigit(value[digit]))
		++digit;
	if (digit > 0)
		digits = ft_strsub(value, 0, digit);
	if (digits)
	{
		res = ft_atoi(digits);
		ft_memdel((void **)&digits);
		return (res);
	}
	return (-1);
}

void	traverse_node(t_treenode **head)
{
	if ((*head)->type == REDIR)
		*head = (((t_redir *)(*head))->cmd);
	else if ((*head)->type == AGGREGATION)
		*head = (((t_aggregate *)(*head))->cmd);
	else if ((*head)->type == CLOSEFD)
		*head = (((t_closefd *)(*head))->cmd);
}
