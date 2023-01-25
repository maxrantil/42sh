/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/01/25 15:52:48 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "keyboard.h"

// t_term	*g_t;

/*
 * It initializes all the variables in the t_term structure to zero
 *
 * @param t the structure that holds all the parameters
 */
static void	ft_init_to_zero(t_term *t)
{
	t->ch = 0;
	t->his = 0;
	t->quote = 0;
	t->bytes = 0;
	t->q_qty = 0;
	t->c_row = 0;
	t->index = 0;
	t->bslash = 0;
	t->heredoc = 0;
	t->total_row = 0;
	t->history_row = -1;
	t->total_row_cpy = 0;
	t->clipboard.type = 0;
}

/*
 * It initializes the terminal
 *
 * @param t the structure that holds all the information about the terminal.
 */
void	ft_init(t_term *t)
{
	ft_memset(t->inp, '\0', BUFF_SIZE);
	ft_memset(t->history_buff, '\0', BUFF_SIZE);
	ft_init_to_zero(t);
	get_term_val(t->term_val);
	t->nl_addr = NULL;
	t->delim = NULL;
	t->prompt_len = (ssize_t)ft_strlen(PROMPT);
	t->m_prompt_len = (ssize_t)ft_strlen(MINI_PROMPT);
	t->c_col = t->term_val[0];
	t->input_cpy = NULL;
	t->fc_flag = false;
	t->config = NULL;
}
