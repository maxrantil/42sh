/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 09:30:04 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/10 21:29:36 by jniemine         ###   ########.fr       */
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
			sh->head = build_tree(&sh->tokens);
			if (sh->head && ((t_semicolon *)sh->head)->left)
				exec_tree(sh->head, &sh->env, sh->terminal, sh);
			shell_end_cycle(sh);
		}
	}
}

static void if_script(int argc, char **argv, t_shell *sh)
{
	int i;

	i = 2;
	if (argc > 1 && ft_strequ(argv[1], "-c"))
	{
		ft_getent();
		ft_session_init(sh);
		ft_history_get(sh->term);
		sh->line = ft_strdup(argv[i++]);
		while(argv[i])
		{
			// ft_printf("ARGV: %s", argv[i]);
			sh->line = ft_strjoin(sh->line, " ");
			sh->line = ft_strjoin(sh->line, argv[i]);
			i++;
		}
		// ft_printf("LINE: %s", sh->line);
		// sh->line = ft_strdup(argv[2]);
		sh->tokens = chop_line(sh->line, sh->tokens, 1);
		sh->head = build_tree(&sh->tokens);
		if (sh->head && ((t_semicolon *)sh->head)->left)
			exec_tree(sh->head, &sh->env, sh->terminal, sh);
		shell_end_cycle(sh);
		// return (1);
			hash_free(sh->ht);
	ft_strdel(&sh->terminal);
		exit(0);
	}
	// return (0);
}

int	main(int argc, char **argv)
{
	t_shell		sh[1];

	if_script(argc, argv, sh);
	ft_getent();
	banner_print();
	ft_session_init(sh);
	// init_alias(&sh[0]);
	ft_history_get(sh->term);
	// if(!if_script(argc, argv, sh))
		main_loop(sh);
	hash_free(sh->ht);
	ft_strdel(&sh->terminal);
	return (0);
}
