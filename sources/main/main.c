/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 09:30:04 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/11 15:24:46 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	main_loop(t_shell *sh)
{
	int	status;

	status = 1;
	sh->term->clipboard.buff = NULL;
	while (status)
	{
		// ft_init_signals();
		// set_signal_keyboard();
		ft_raw_enable(sh);
		if (ft_keyboard(sh->term) == 1)
		{
			ft_history_write_to_file(sh->term);
			jobs_exit_check(sh);
			if (sh->exit_confirm >= 0)
				ft_putstr("There are stopped jobs.\n");
			else
				status = 0;
		}
		ft_raw_disable(sh->orig_termios);
		if (*(sh->term->inp))
		{
			sh->line = ft_lexer(sh->term);
			// alias_convert_line(&(sh->line), sh);
			sh->tokens = chop_line(sh->line, sh->tokens, 1);
			// ft_printf("b\n");
			// sleep(2);
			sh->head = build_tree(&sh->tokens);
			// ft_printf("c\n");
			// sleep(3);
			if (sh->head && ((t_semicolon *)sh->head)->left)
				exec_tree(sh->head, &sh->env, sh->terminal, sh);
			// ft_printf("d\n");
			// sleep(3);
			shell_end_cycle(sh);
			// ft_printf("e\n");
			// print_alias_all(sh->alias, sh);
			// sleep(3);
		}
	}
}

// 							b a; b a ; a;a;
int	main(void)
{
	t_shell		sh[1];

	ft_getent();
	banner_print();
	ft_session_init(sh);
	init_alias(&sh[0]);
	ft_history_get(sh->term);
	main_loop(sh);
	hash_free(sh->ht);
	ft_strdel(&sh->terminal);
	return (0);
}
