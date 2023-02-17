/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 09:30:04 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/17 11:59:53 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	interactive_mode(t_shell *sh, int *status)
{
	ft_raw_enable(sh);
	if (ft_keyboard(sh->term) == 1)
	{
		ft_history_write_to_file(sh->term);
		jobs_exit_check(sh);
		if (sh->exit_confirm >= 0)
			ft_putstr("There are stopped jobs.\n");
		else
			*status = 0;
	}
	ft_raw_disable(sh->orig_termios);
}

void	main_loop(t_shell *sh)
{
	int	status;

	status = 1;
	sh->term->clipboard.buff = NULL;
	while (status)
	{
		interactive_mode(sh, &status);
		reap_process(sh);
		if (*(sh->term->inp))
		{
			sh->line = ft_lexer(sh->term);
			alias_convert_line(&(sh->line), sh);
			sh->tokens = chop_line(sh->line, sh->tokens, 1);
			sh->head = build_tree(&sh->tokens);
			if (sh->head && ((t_semicolon *)sh->head)->left)
				exec_tree(sh->head, &sh->env, sh->terminal, sh);
			shell_end_cycle(sh);
		}
	}
}

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
