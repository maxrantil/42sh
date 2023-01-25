/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:13:13 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/25 15:31:03 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	delete_var(t_session *sesh, int *i)
{
	ft_strdel(&sesh->intr_vars[*i]);
	sesh->intr_vars[*i] = sesh->intr_vars[*i + 1];
	while (sesh->intr_vars[*i + 1])
	{
		sesh->intr_vars[*i] = sesh->intr_vars[*i + 1];
		*i += 1;
	}
	sesh->intr_vars[*i] = NULL;
}

static int find_var_key(t_session *sesh, char *cmd, int var_len)
{
	int	i;
	int	k;
	int ret;

	i = 0;
	ret = 0;
	k = 0;
	while (sesh->intr_vars[i])
	{
		if (ft_strncmp(sesh->intr_vars[i], cmd, var_len) == 0
			&& sesh->intr_vars[i][var_len - 1] == '=')
		{
			ft_env_append(sesh, &sesh->intr_vars[i]);
			delete_var(sesh, &i);
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

int	print_exported(t_session *sesh, char *cmd)
{
	char		*value;
	char		*key;
	int			i;
	static int	first;

	(void)cmd;
	i = 0;
	value = NULL;
	while (sesh->env[i])
	{
		value = ft_strchr(sesh->env[i], '=') + 1;
		key = ft_strndup(sesh->env[i], \
		ft_strlen(sesh->env[i]) - ft_strlen(value));
		if (ft_strequ(key, "_=") && !first)
		{
			first = 1;
			ft_printf("export %s\"%s\"\n", key, value);
		}
		else if (ft_strequ(key, "_=") && first)
			i++;
		else
			ft_printf("export %s\"%s\"\n", key, value);
		i++;
		ft_strdel(&key);
	}
	return (0);
}

/**
 * It checks for a valid key, then either replaces an existing key or appends
 * a new key.
 *
 * @param sesh the session struct
 * @param cmd The command line arguments
 *
 * @return The return value is the exit status of the command.
 */
int	ft_export(t_session *sesh, char **cmd)
{
	int		i;
	char	*key;

	i = 0;
	sesh->exit_stat = 0;
	key = NULL;
	if (!cmd[1])
	{
		print_exported(sesh, NULL);
		return (0);
	}
	while (*(cmd + ++i))
	{
		key = ft_strjoin(*(cmd + i) ,"=");
		if (ft_strchr(*(cmd + i), '='))
		{
			if (!key_check(*(*(cmd + i))))
			{
				key_check_fail_msg(cmd, i);
				sesh->exit_stat = 1;
			}
			else if (!ft_env_replace(sesh, *(cmd + i), NULL))
				ft_env_append(sesh, cmd + i);
		}
		find_var_key(sesh, key, ft_strlen(key));
		ft_strdel(&key);
	}
	return (0);
}
