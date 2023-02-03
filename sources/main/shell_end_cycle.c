/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_end_cycle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 14:26:23 by jniemine          #+#    #+#             */
/*   Updated: 2023/02/03 14:00:12 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	ft_reset_tmp_env(t_shell *sh)
{
	int		i;
	char	*key;
	char	**env;

	i = -1;
	if (sh->tmp_env_key)
	{
		while (sh->tmp_env_key[++i])
		{
			key = ft_strchr(sh->tmp_env_key[i], '=');
			if (key)
			{
				key = ft_strsub(sh->tmp_env_key[i], 0, key - \
					sh->tmp_env_key[i]);
				env = ft_env_get(sh, key, sh->env);
				ft_strdel(env);
				*env = ft_strdup(sh->tmp_env_key[i]);
				ft_strdel(&key);
			}
			else
				ft_env_remove(sh, sh->tmp_env_key[i]);
			ft_strdel(&sh->tmp_env_key[i]);
		}
		ft_memdel((void **)&sh->tmp_env_key);
	}
}

static void	check_hash(t_shell *sh)
{
	if (!ft_env_get(sh, "PATH", sh->env))
		hash_clear(sh->ht);
}

/**
 * It resets the tokens and sets the return value to 0
 *
 * @param sh the session struct
 */
void	shell_end_cycle(t_shell *sh)
{
	free_node(sh->head);
	free_tokens(&sh->tokens);
	reset_fd(sh->terminal);
	ft_reset_tmp_env(sh);
	check_hash(sh);
}
