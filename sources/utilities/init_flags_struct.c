/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_flags_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:41:52 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/14 13:42:16 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	init_flags_struct(t_token_flags *flags)
{
	flags->quote = 0;
	flags->braces = 0;
	flags->braces_count = 0;
}
