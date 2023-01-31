/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_or_create.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:38:55 by mviinika          #+#    #+#             */
/*   Updated: 2023/01/31 09:54:32 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

char	*remove_braces(char *str)
{
	char	*new;
	int		i;
	int		k;

	k = 0;
	i = 1;
	ft_printf("%c\n", str[1]);
	if (!str[1] || str[1] != '{')
		return (str);
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

char	*subst_param(t_shell *sh, char *var, char *subst, int format)
{
	char	*expanded;
	char	**temp;

	expanded = NULL;
	temp = (char **)ft_memalloc(sizeof(char *) * 2);
	temp[0] = ft_expansion_dollar(sh, var);
	//ft_printf("temp [%s]\n", temp[0]);
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
		ft_printf("[%s]\n", var);
		if (!*temp[0])
		{
			expanded = ft_strdup(subst + 1);
			//ft_strdel(&temp[0]);
			//temp[0] = ft_strjoin(var + 1, "=");
			temp[0] = ft_strjoin(var + 1, subst);
			ft_printf("temp [%s]\n", temp[0]);
			add_var(sh, temp);
		}
		else
			expanded = ft_strdup(temp[0]);
	}
	else if (format == 2)
	{
	//	ft_printf("questionmark[%s]\n", var);
		if (!*temp[0] && subst[1])
			ft_printf("42sh: %s: %s\n", var + 1, subst + 1);
		else if (!*temp[0] && !subst[1])
			ft_printf("42sh: %s: parameter null or unset\n", var + 1);
		else
			expanded = ft_strdup(temp[0]);
	}
	else if (format == 3)
	{
		ft_printf("plus sign[%s] %s\n", var, subst);
		if (temp[0][0])
		{
			ft_printf("temp %s plus sign[%s] %s\n",temp[0], var, subst);
			if (subst && *subst)
			{
				if (subst[0] == '+')
					expanded = ft_strdup(subst + 1);
				else
					expanded = ft_strdup(subst);
			}
			else
				expanded = ft_strnew(1);
			ft_printf("expanded plus %s\n", expanded);
		}
		else
			expanded = ft_strnew(1);
	}
	return (expanded);
}

char	*retokenize(t_shell *sh, char *subst, int *i)
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

int	format_mode(char op)
{
	int		format;

	format = -1;
	ft_printf("subst mode %c\n", op);
	if (op == '-')
		format = 0;
	else if (op == '=')
		format = 1;
	else if (op == '?')
		format = 2;
	else if (op == '+')
		format = 3;
	return (format);
}

static int check_vari(char *var)
{
	int	i;
	
	i = 1;
	if (ft_isalpha(var[0]) || (!ft_isalpha(var[0]) && var[0] != '_'))
		return (1);
	// while(var[i])
	// {
		
	// }
	return (0);
}

char *substitute_or_create(t_shell *sh, char *cmd, int *ret)
{
	int		i;
	int		k;
	char	*expanded;
	char	*strip;
	char	*var;
	char	*subs;
	char	op;
	int		format;
	char	**list;

	i = 0;
	subs = ft_strnew(1);
	expanded = ft_strnew(1);
	var = ft_strnew(1);
	op = 0;
	k = 0;
	format = -1;
	strip = remove_braces(cmd);
	list = (char **)ft_memalloc(sizeof(char *) * 100);
	// if (ft_strnequ(cmd, "${#", 3))
	// 		expanded = count_letters(sh, strip);
	ft_printf("sisaantuleva matsku [%s]\n", strip);
	ft_printf("sisaantuleva matsku [%s]\n", cmd);
	if (ft_strchr(strip, ':'))
	{
		ft_printf("stripped [%s]\n",strip);
		subs = ft_strdup(ft_strchr(strip, ':'));
		ft_printf("substitution [%s]\n",subs);
		subs = (char *)ft_memmove(subs, subs + 1, ft_strlen(subs));
		ft_printf("substitution [%s]\n",subs);
		op = subs[0];
		ft_printf("substitution [%s]\n",subs);
		var = ft_strndup(strip, ft_strlen(strip) - (ft_strlen(subs)));
		if (!check_vari(var))
		{
			*ret = -1;
			return (var);
		}
		else
			var[ft_strlen(var - 1)] = '\0';
		ft_printf("var [%s] substitution [%s]\n", var, subs);
		// while (subs[i])
		// {
		// 	list[k++] = retokenize(sh, subs, &i);
		// }
		// k = 0;
		// while (list[k])
		// 	ft_printf("list %s\n", list[k++]);
		// exit(1);
	}
	else if (ft_strchr(strip, '#'))
	{
		subs = ft_strdup(ft_strchr(strip, '#'));
		op = subs[0];
	}
	else if (ft_strchr(strip, '%'))
	{
		subs = ft_strdup(ft_strchr(strip, '%'));
		op = subs[0];
	}
	else
	{
		expanded = ft_expansion_dollar(sh, strip);
		ft_printf("tassa\n");
	}
	ft_printf("expanded asdfasfasfasfd[%s]\n", subs);
	if (ft_strnequ(subs + 1, "${", 2))
		subs = substitute_or_create(sh, subs + 1, ret);
	format = format_mode(op);
	if (!*expanded)
		expanded = subst_param(sh, var, subs, format);
	//ft_printf("expanded [%s]\n", expanded);
	return (expanded);
}
