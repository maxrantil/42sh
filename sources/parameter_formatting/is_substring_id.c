/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_substring_id.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:38:51 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/10 17:02:51 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int	is_substring_id(char *needle)
{
	return ((ft_strnequ(needle, "${", 2) && ft_strchr(needle , '#'))
		|| (ft_strnequ(needle, "${", 2) && ft_strchr(needle , '%')));
}
