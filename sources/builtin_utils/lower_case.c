/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lower_case.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:02:16 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/17 12:23:19 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

char	*lower_case(char *cmd)
{
	int		i;
	char	*str;

	i = -1;
	str = ft_strdup(cmd);
	while (str[++i])
		str[i] = ft_tolower(str[i]);
	return (str);
}
