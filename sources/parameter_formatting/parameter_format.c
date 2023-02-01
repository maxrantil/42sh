/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:40:05 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/01 11:43:33 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	check_syntax(char *cmd)
{
	// int	i;
	// int	valid;

	// i = 0;
	// valid = -1;
	//ft_printf("kljsadhfgklj %c\n", cmd[ft_strlen(cmd) -1]);
	if (ft_strnequ(cmd, "${", 2) && cmd[ft_strlen(cmd) -1] == '}')
	{
		// i += 2;
		// valid = 0;
		// if (cmd[i] == '#')
		// 	valid += 1;
		// while (cmd[i])
		// {
		// 	if (cmd[i] == ':')
		// 		valid += 1;
		// 	else if (cmd[i] == '}')
		// 		valid += 1;
		// 	i++;
		// }
		// if (valid == 2)
		return (1);
		// else
		// 	ft_printf("no %d\n", valid);
	}
	return (0);
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

static char	*retokenize(t_shell *sh, char *subst, int *i)
{
	char 	*trimmed;
	int		k;
	int		j;
	int		open;
	char	*fresh;

	k = 0;
	j = 0;
	open = 0;
	(void)sh;
	trimmed = ft_strtrim(subst);
	fresh = ft_strnew(ft_strlen(subst));
	while (trimmed[*i])
	{
		fresh[k++] = trimmed[(*i)++];
		if (fresh[0] == '$')
		{
			if (trimmed[*i] == '{')
				open += 1;
		}
		if (trimmed[*i] == '}')
		{
			open -= 1;
			if (open == 0)
			{
				fresh[k++] = trimmed[(*i)++];
				break ;
			}
		}
		if (trimmed[*i] == '$' && !open)
			break ;
	}
	ft_strdel(&trimmed);
	return (fresh);
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
static char	*remove_braces(char *str)
{
	char	*new;
	int		i;
	int		k;

	k = 0;
	i = 1;
	str[1] = str[2];
	str[ft_strlen(str) - 1] = '\0';
	ft_printf("%s\n", str);
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
	ft_printf("%s\n", str);
	new = ft_strdup(str);
	return (new);
}

int is_legit(char flag)
{
	if (flag == '\0')
		return (0);
	return (flag == ':' || flag == '%' || flag == '#');
}

char *get_flag(char *cmd)
{
	if (ft_strchr(cmd, ':'))
		return(ft_strchr(cmd, ':'));
	else if (ft_strchr(cmd, '#'))
		return(ft_strchr(cmd, '#'));
	else if (ft_strchr(cmd, '%'))
		return(ft_strchr(cmd, '%'));
	return (NULL);
}

// static int is_good_var(char *var)
// {
// 	if ((var[1] && !ft_isalpha(var[1])) 
// 		|| (!ft_isalpha(var[1]) && var[1] != '_')
// 		|| (!ft_isalpha(var[1]) && var[1] != '!'))
// 		return (-1);
// 	return (1);
// }

int	param_format(t_shell *sh, char **cmd)
{
	int		i;
	int		k;
	int		j = 0;
	char	*expanded;
	//char	*strip;
	char	*var;
	char	*subs;
	char	op;
	int		format;
	char	**list;
	char	*strip;
	char	*flag;
	int		ret;

	ret = 0;
	i = -1;
	k = 0;
	subs = ft_strnew(1);
	expanded = ft_strnew(1);
	var = ft_strnew(1);
	op = 0;
	format = -1;
	list = (char **)ft_memalloc(sizeof(char *) * 100);
	while (cmd[++i])
	{
		if (check_syntax(cmd[i]))
		{
			flag = get_flag(cmd[i]);
			if (flag && is_legit(flag[0]))
			{
				strip = ft_strdup(cmd[i]);
				remove_braces(strip);
				ft_printf("flag %c\n", flag[0]);
				subs = ft_strdup(get_flag(strip + 1));
				op = subs[0];
				subs = (char *)ft_memmove(subs, subs + 1, ft_strlen(subs));
				var = ft_strndup(strip, ft_strlen(strip) - (ft_strlen(subs)));
				ft_printf("var %s\n", var);
			}
			else
			{
				ft_printf("flag %s\n", cmd[i]);
				expanded = ft_expansion_dollar(sh, cmd[i]);
				ft_printf("expanded %s\n", expanded);
				ft_strdel(&cmd[i]);
				cmd[i] = ft_strdup(expanded);
				break ;
			}
			while (subs[j])
			{
				list[k++] = retokenize(sh, subs, &j);
			}
			k = 0;
			while (list[k])
				ft_printf("lisdfsddfdsst %s\n", list[k++]);
			k = 0;
			while (list[k])
			{
				
				if (ft_strnequ(list[k], "${", 2) && op == ':')
					expanded = ft_strjoin(expanded, substitute_or_create(sh, list[k++], &ret));
				else if ((ft_strnequ(list[k], "${", 2) && op == '%')
					|| (ft_strnequ(list[k], "${", 2) && op == '#'))
					expanded = ft_strjoin(expanded, search_from_var(sh, list[k++], &ret));
				else
					expanded = ft_strjoin(expanded, list[k++]);
				
				if (ret == -1)
					return (1);
			}
			ft_strdel(&subs);
			subs = ft_strjoin(var, expanded);
			ft_strdel(&expanded);
			if (op == ':')
				expanded = substitute_or_create(sh, subs, &ret);
			else if (flag[0] == '%' || flag[0] == '#')
			{
				ft_printf("%s\n", subs);
				expanded = search_from_var(sh, subs, &ret);
			}
				
			if (!expanded || !*expanded)
			{
				ft_printf("42sh: %s: bad substitution\n", cmd[i]);
				return -1;
			}
			ft_strdel(&cmd[i]);
			cmd[i] = ft_strdup(expanded);
			ft_strdel(&var);
			ft_strdel(&subs);
			ft_strdel(&expanded);
			ft_strdel(&strip);
		}
	}
	return (0);
}
