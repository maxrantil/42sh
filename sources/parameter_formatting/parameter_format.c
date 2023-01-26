/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:40:05 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/26 09:56:21 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	check_syntax(char *cmd)
{
	int	i;
	int	valid;

	i = 0;
	valid = -1;
	//ft_printf("kljsadhfgklj %c\n", cmd[ft_strlen(cmd) -1]);
	if (ft_strnequ(cmd, "${", 2) && cmd[ft_strlen(cmd) -1] == '}')
	{
		i += 2;
		valid = 0;
		if (cmd[i] == '#')
			valid += 1;
		while (cmd[i])
		{
			if (cmd[i] == ':')
				valid += 1;
			else if (cmd[i] == '}')
				valid += 1;
			i++;
		}
		if (valid == 2)
			return (1);
		else
			ft_printf("no %d\n", valid);
	}
	return (0);
}

char	*remove_braces(char *str)
{
	char	*new;
	int		i;
	int		k;

	k = 0;
	i = 0;
	new = ft_strnew(ft_strlen(str));
	while (str[i])
	{
		if (str[i] == '{' || str[i] == '}')
			i++;
		if(str[i] == '\0')
			break ;
		new[k++] = str[i++];
	}
	return (new);
}

void add_var_to_list(t_shell *sh, char *var, char *subst)
{
	int	i;

	i = 0;
	while (sh->intr_vars[i])
		i++;
	sh->intr_vars[i] = ft_strjoin(var + 1, subst);
}

int	is_in_var_or_env(t_shell *sh, char *var)
{
	int i;
	int	var_len;
	char	*key;

	i = -1;

	key = ft_strjoin(var, "=");
	var_len = ft_strlen(key);
	ft_printf("key %s\n", key);
	while(sh->intr_vars[++i])
	{
		if (ft_strncmp(sh->intr_vars[i], key, var_len) == 0
			&& sh->intr_vars[i][var_len - 1] == '=')
			return (1);
	}
	i = -1;
	while(sh->env[++i])
	{
		if (ft_strncmp(sh->env[i], key, var_len) == 0
			&& sh->env[i][var_len - 1] == '=')
			return (1);
	}
	return (0);
}

char	*subst_param(t_shell *sh, char *var, char *subst, int format)
{
	char	*expanded;
	char	**temp;

	expanded = NULL;
	temp = (char **)ft_memalloc(sizeof(char *) * 2);
	temp[0] = ft_expansion_dollar(sh, var);
	ft_printf("temp [%s]\n", temp[0]);
	temp[1] = NULL;
	if (format == 0)
	{
		ft_printf("[%s]\n", temp[0]);
		if (!temp[0])
			expanded = ft_strdup(subst + 1);
		else
			expanded = ft_strdup(var);
		return (expanded);
	}
	else if (format == 1)
	{
		ft_printf("[%s]", var);
		if (!*temp[0])
		{
			expanded = ft_strdup(subst + 1);
			ft_strdel(&temp[0]);
			temp[0] = ft_strjoin(var + 1, subst);
			ft_printf("temp [%s]\n", temp[0]);
			add_var(sh, temp);
			//add_var_to_list(sh, var, subst);
		}
		else
			expanded = ft_strdup(temp[0]);

	}
	else if (format == 2)
	{
		ft_printf("questionmark[%s]\n", var);
		if (!*temp[0] && subst[1])
			ft_printf("21sh: %s: %s\n", var + 1, subst + 1);
		else if (!*temp[0] && !subst[1])
			ft_printf("21sh: %s: parameter null or unset\n", var + 1);
		else
			expanded = ft_strdup(temp[0]);

	}
	else if (format == 3)
	{
		ft_printf("plus sign[%s] %s\n", var, subst);
		if (temp[0][0])
			expanded = ft_strdup(subst + 1);
		else
			expanded = ft_strnew(1);
	}
	return (expanded);
}

int	format_mode(char *var)
{
	int		format;
	char	subst_mode;

	format = -1;
	subst_mode = var[0];
	ft_printf("subst mode %c\n", subst_mode);
	if (subst_mode == '-')
		format = 0;
	else if (subst_mode == '=')
		format = 1;
	else if (subst_mode == '?')
		format = 2;
	else if (subst_mode == '+')
		format = 3;
	return (format);
}

char *count_letters(t_shell *sh, char *cmd)
{
	int		i;
	int		k;
	char	*expanded;
	char	*var;

	i = 0;
	k = 0;
	expanded = NULL;
	var = ft_strnew(ft_strlen(cmd));
	while (cmd[i])
	{
		if (cmd[i] == '#')
			i++;
		var[k++] = cmd[i++];
	}
	i = 1;
	ft_printf("%s\n", var);
	// while(var[i])
	// {
	// 	if (!ft_isalpha(cmd[i]) && cmd[i] != '_' && cmd[i] != '!')
	// 		return (NULL);
	// 	i++;
	// }
	expanded = ft_expansion_dollar(sh, var);
	ft_strdel(&var);
	return (ft_itoa(ft_strlen(expanded)));
}

int	param_format(t_shell *sh, char **cmd)
{
	int		i;
	char	*expanded;
	char	*strip;
	char	*var;
	char	*subs;
	int		format;

	i = -1;
	subs = NULL;
	expanded = NULL;
	format = -1;
	while (cmd[++i])
	{
		if (check_syntax(cmd[i]))
		{
			strip = remove_braces(cmd[i]);
			if (ft_strnequ(cmd[i], "${#", 3))
				expanded = count_letters(sh, strip);
			else
			{
				subs = ft_strdup(ft_strchr(strip, ':') + 1);
				var = ft_strndup(strip, ft_strlen(strip) - ft_strlen(subs) - 1);
				format = format_mode(subs);
			}
			ft_printf("stripped %s variable %s format %d\n", strip, subs, format);
			if (format != -1)
				expanded = subst_param(sh, var, subs, format);
			if (expanded == NULL)
			{
				return (-1);
			}
			else if (expanded[0] == '$')
				expanded = ft_expansion_dollar(sh, var);
			ft_strdel(&cmd[i]);
			cmd[i] = ft_strdup(expanded);
			ft_strdel(&var);
			ft_strdel(&subs);
			ft_printf("Expanded %s\n", cmd[i]);
		}
	}
	return (0);
}
