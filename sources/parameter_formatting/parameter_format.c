/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:40:05 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/27 15:57:04 by mviinika         ###   ########.fr       */
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

	i = -1;
	k= 0;
	subs = ft_strnew(1);
	expanded = ft_strnew(1);
	var = ft_strnew(1);
	op = 0;
	format = -1;
	list = (char **)ft_memalloc(sizeof(char *) * 100);
	// strip = remove_braces(cmd);
	while (cmd[++i])
	{
		if (check_syntax(cmd[i]))
		{
			strip = remove_braces(cmd[i]);
			ft_printf("stripped %s\n", cmd[i]);
			subs = ft_strdup(ft_strchr(strip, ':') + 1);
			ft_printf("not in subs %s\n", subs);
			op = subs[0];
			subs = (char *)ft_memmove(subs, subs + 1, ft_strlen(subs));
			ft_printf("not in subs %s\n", subs);
			var = ft_strndup(strip, ft_strlen(strip) - (ft_strlen(subs)));
			ft_printf("not in var %s\n", var);
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
				if (ft_strnequ(list[k], "${", 2))
					expanded = ft_strjoin(expanded, substitute_or_create(sh, list[k++]));
				else
					expanded = ft_strjoin(expanded, list[k++]);
			}
			ft_printf("final expand %s %s\n",var, expanded);
			ft_strdel(&subs);
			subs = ft_strjoin(var, expanded);
			ft_printf("variable %s final subst %s\n", var, subs);
			ft_strdel(&expanded);
			expanded = substitute_or_create(sh, subs);
			ft_printf("final subst %s\n", expanded);
			//expanded = substitute_or_create(sh, cmd[i]);
			// if (ft_strnequ(cmd[i], "${#", 3))
			// 	expanded = count_letters(sh, strip);
			// else
			// {
			// 	if (ft_strchr(strip, ':'))
			// 	{
			// 		subs = ft_strdup(ft_strchr(strip, ':') + 1);
			// 		op = subs[0];
			// 		subs = (char *)ft_memmove(subs, subs + 1, ft_strlen(subs));
			// 		if (ft_strnequ(subs, "${", 2))
			// 			param_format(sh, &subs);
			// 	}
			// 	else if (ft_strchr(strip, '#'))
			// 	{
			// 		subs = ft_strdup(ft_strchr(strip, '#'));
			// 		op = subs[0];
			// 	}
			// 	else if (ft_strchr(strip, '%'))
			// 	{
			// 		subs = ft_strdup(ft_strchr(strip, '%'));
			// 		op = subs[0];
			// 	}
			// 	var = ft_strndup(strip, ft_strlen(strip) - ft_strlen(subs) - 1);
			// 	format = format_mode(subs);
			// }
			// ft_printf("var %s subs %s format %d operator %c\n", var, subs, format, op);
				
			// if (expanded == NULL)
			// {
			// 	return (-1);
			// }
			// else if (expanded[0] == '$')
			// 	expanded = ft_expansion_dollar(sh, var);
			// ft_printf("Expanded %s\n", expanded);
			ft_strdel(&cmd[i]);
			cmd[i] = ft_strdup(expanded);
			ft_strdel(&var);
			ft_strdel(&subs);
			ft_strdel(&expanded);
			
		}
	}
	return (0);
}
