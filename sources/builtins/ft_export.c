/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:13:13 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/23 14:51:09 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	find_var_key(t_shell *sh, char *cmd, int var_len)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (sh->intr_vars[i])
	{
		if (ft_strncmp(sh->intr_vars[i], cmd, var_len) == 0
			&& sh->intr_vars[i][var_len - 1] == '=')
		{
			ft_env_append(sh, &sh->intr_vars[i]);
			delete_var(sh, &i);
			ret = 1;
			break ;
		}
		i++;
	}
	return (ret);
}

static void	key_check_fail_msg(char **cmd, int i)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(*cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("`", 2);
	ft_putstr_fd(*(cmd + i), 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static int	key_check(int ch)
{
	if (ch == '=' || (ft_isspecial(ch) && ch != '_') || ft_isdigit(ch))
		return (0);
	else
		return (1);
}

static void	insert_variable(t_shell *sh, char **cmd, int i)
{
	if (!key_check(*(*(cmd + i))))
	{
		key_check_fail_msg(cmd, i);
		sh->exit_stat = 1;
	}
	else if (!ft_env_replace(sh, *(cmd + i), NULL))
		ft_env_append(sh, cmd + i);
}

/**
 * It checks for a valid key, then either replaces an existing key or appends
 * a new key.
 *
 * @param sh the session struct
 * @param cmd The command line arguments
 *
 * @return The return value is the exit status of the command.
 */
int	ft_export(t_shell *sh, char **cmd, int opt)
{
	int		i;
	char	*key;

	i = 0;
	if (opt)
		i = -1;
	sh->exit_stat = 0;
	key = NULL;
	if (check_export_print(sh, cmd) && !opt)
		return (0);
	while (*(cmd + ++i))
	{
		key = ft_strjoin(*(cmd + i), "=");
		if (ft_strnequ(key, "PATH=", 5))
			hash_clear(sh->ht);
		if (ft_strchr(*(cmd + i), '='))
			insert_variable(sh, cmd, i);
		find_var_key(sh, key, ft_strlen(key));
		ft_strdel(&key);
	}
	return (0);
}
