/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_fetch_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:04:15 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/02 17:21:44 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
    How to refer to a job according to bash manual

    


*/





// /* static t_bg_jobs   *search_via_percent_ch(char sign, t_bg_jobs *head)
// {
//     int count;
//     count = 0;
//     while (head)
//     {
//         if (sign == head->queue || (!head->next && !count))
//             return (head);
//         count++;
//         head = head->next;
//     }
//     return (NULL);
// } */

// static t_bg_jobs   *search_via_cmd(char *cmd, t_bg_jobs *head)
// {
//     t_bg_jobs  *ret;

//     ret = NULL;
//     while (head)
//     {
//         if (!ft_strcmp(cmd, *head->command))
//         {
//             if (ret)
//                 return (NULL);
//             else
//                 ret = head;
//         }
//         head = head->next;
//     }
//     return (ret);
// }

static t_bg_jobs    *search_via_index(int index, t_bg_jobs *head)
{
    while (head)
    {
        if (index == head->index)
            return (head);
        head = head->next;
    }
    return (head);
}

t_bg_jobs   *process_getpid(int index, /*char *cmd,  char sign, */ t_bg_jobs *head)
{
    if (index)
        return (search_via_index(index, head));
    // if (cmd)
    //     return (search_via_cmd(cmd, head));
    /* if (sign)
        return (search_via_percent_ch(sign, head)); */
    return (NULL);
}

t_bg_jobs    *bg_fetch_node(t_bg_jobs *head, char *cmd)
{
	// if (!cmd || !ft_strcmp("%%", cmd) || !ft_strcmp("%+", cmd)) // fetch the first one in the queue
	// 	return (process_getpid(0, NULL, /* '+', */ head));
	// if (!ft_strcmp("%-", cmd)) // fetch the second one in the queue
	// 	return (process_getpid(0, NULL, /* '-', */ head));
	// if (*cmd == '%')
	// 	cmd++;
	// if (ft_isdigit(*cmd))
	// 	return (process_getpid(ft_atoi(cmd) - 1, /* NULL, */ 0, head));
	// return (process_getpid(0, cmd, /* 0, */ head));
	if (ft_isdigit(*cmd))
		return (process_getpid(ft_atoi(cmd) - 1, head));
	return (process_getpid(0, head));
}
