/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_substring_id.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:38:51 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/10 13:24:46 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int	is_substring_id(char *needle)
{
	return ((ft_strnequ(needle, "${", 2) && ft_strchr(needle , '#'))
		|| (ft_strnequ(needle, "${", 2) && ft_strchr(needle , '%')));
}
