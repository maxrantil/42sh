/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_fetch_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:04:15 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/02 14:36:46 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

t_bg_jobs    *bg_fetch_node(t_bg_jobs *head, char *cmd)
{
    int         index;
    t_bg_jobs   *ptr;

    index = 0;
    index = ft_atoi(cmd) - 1; // make a check for negative or and owerflow
    ptr = head;
    if (index >= 0)
    {
        while (ptr && index != ptr->index)
            ptr = ptr->next;
        if (ptr)
            return (ptr);
    }
	// if (!cmd || !ft_strcmp("%%", cmd) || !ft_strcmp("%+", cmd))
	// 	return (process_getpid(0, NULL, /* '+', */ head));
	// if (!ft_strcmp("%-", cmd))
	// 	return (process_getpid(0, NULL, /* '-', */ head));
	// if (*cmd == '%')
	// 	cmd++;
	// if (ft_isdigit(*cmd))
	// 	return (process_getpid(ft_atoi(cmd), /* NULL, */ 0, head));
	// else
	// 	return (process_getpid(0, cmd, /* 0, */ head));
	return (NULL);
}
