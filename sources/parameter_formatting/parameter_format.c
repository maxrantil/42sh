/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:40:05 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/09 14:37:04 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

extern t_shell	*g_sh;

static int	check_syntax(char *cmd)
{
	int	len;

	if (!cmd)
		return 0;
	len = ft_strlen(cmd) - 1;
	if (ft_strnequ(cmd, "${", 2) && cmd[len] == '}')
		return (1);
	return (0);
}

static int	is_legit(char *flag)
{
	if (*flag == '\0')
		return (0);
	else if (flag[0] == ':')
		return (flag[1] == '-' || flag[1] == '+' || flag[1] == '=' || flag[1] == '?');
	return ((flag[0] == '%'  && flag[1]) || (flag[0] == '#' && flag[1]));
}

// static int	is_legit_format(char *format)
// {
// 	if (format == '\0')
// 		return (0);
// 	return (format == '+' || format == '-' || format == '=');
// }

// static int check_form_flag(char flag)
// {
// 	return (flag == '%' || flag == '#' || flag == ':' || flag == '}');
// }

static char	*get_operator(char *cmd, int *ret)
{
	int	i;

	i = 2;
	(void)ret;
	//ft_printf("getting operator %s\n",cmd);
	if (!cmd[1])
		return (NULL);
	while (ft_isalnum(cmd[i]))
		i++;
	ft_printf("getting operator %s\n",cmd + i);
	if (!is_legit(&cmd[i]) && cmd[i] != '}')
		*ret = -1;
	return (cmd + i);
}

static char	*get_flag(char *cmd, int *ret)
{
	int	i;

	i = 2;
	(void)ret;
	//ft_printf("getting flag %s\n",cmd);
	if (!cmd[1])
		return (NULL);
	while (ft_isalnum(cmd[i]))
		i++;
	// if (!check_flag(cmd[i]))
	// 	*ret = -1;
	return (cmd + i);
}

static void	init_pa(t_param *pa)
{
	pa->list = (char **)ft_memalloc(sizeof(char *) * 100);
	pa->expanded = ft_strnew(1);
	pa->op = 0;
}

static int splits(char *cmd, t_param *pa, int *ret)
{
	pa->oper = get_operator(cmd, ret);
	if (is_legit(pa->oper))
	{
		pa->strip = ft_strdup(cmd);
		remove_braces(pa->strip);
		pa->subs = ft_strdup(get_flag(pa->strip + 1, ret));
		ft_printf("%s\n", pa->subs);
		pa->op = pa->subs[0];
		pa->subs = \
		(char *)ft_memmove(pa->subs, pa->subs + 1, ft_strlen(pa->subs));
		pa->var = \
		ft_strndup(pa->strip, ft_strlen(pa->strip) - (ft_strlen(pa->subs)));
		ft_printf("expanded [%s]: \n", pa->subs);
	}
	else if (*ret == -1)
	{
		ft_printf("42sh: %s: bad substitution\n", cmd);
		return (1);
	}
	else
	{
		ft_strdel(&pa->expanded);
		pa->strip = ft_strdup(cmd);
		remove_braces(pa->strip);
		pa->expanded = ft_expansion_dollar(g_sh, pa->strip);
		ft_printf("expanded %s: \n", pa->expanded);
		//ft_strdel(&cmd);
		ft_strdel(&pa->strip);
		//cmd = ft_strdup(pa->expanded);
		*ret = 2;
		return (1);
	}
	return (0);
}

static void	retoken_into_list(t_param *pa)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (pa->subs[j])
	{
		pa->list[i++] = retokenize(pa->subs, &j);
	}
		
}

char	*variable_length(char *str)
{
	char	*var;
	char	*temp;
	int		i;
	int		k;

	i = 0;
	k = 0;
	var = ft_strnew(ft_strlen(str));
	while (str[i])
	{
		var[k++] = str[i++];
		if (str[i] == '#')
			i++;
	}
	temp = ft_expansion_dollar(g_sh, var);
	i = ft_strlen(temp);
	return(ft_itoa(i));
}

static int expander(t_param *pa, int ret)
{
	int	i;
	char	*temp;
	char	*subs;

	i = -1;
	while (pa->list[++i])
	{
		pa->flag = get_flag(pa->list[i], &ret);
		// if (!pa->flag)
		// 	pa->expanded = ft_strnew(1);
		ft_printf("pa list %s  [%c]\n",  pa->list[i], pa->flag[0]);
		if (ft_strnequ(pa->list[i], "${", 2) && pa->flag[0] == ':')
		{
			subs = substitute_or_create(g_sh, pa->list[i], &ret);
			temp = ft_strjoin(pa->expanded, subs);
			ft_strdel(&pa->expanded);
			pa->expanded = ft_strdup(temp);
			ft_strdel(&subs);
			ft_strdel(&temp);
		}
		else if ((ft_strnequ(pa->list[i], "${", 2) && pa->flag[0] == '#')
			|| (ft_strnequ(pa->list[i], "${", 2) && pa->flag[0] == '%'))
		{
			
			subs = search_from_var(g_sh, pa->list[i], &ret);
			temp = ft_strjoin( pa->expanded, subs);
			ft_strdel(&pa->expanded);
			pa->expanded = ft_strdup(temp);
			ft_printf(" expanded [%s] \n", pa->expanded);
			ft_strdel(&subs);
			ft_strdel(&temp);
		}
		else
			pa->expanded = ft_strupdate(pa->expanded, pa->list[i]);
		if (ret == -1 || !*pa->expanded)
			return (1);
	}
	return (0);
}

static int	joiner(t_shell *sh, t_param *pa, char *cmd, int ret)
{
	char	*temp;
	char	*subs;

	ft_strdel(&pa->subs);
	pa->subs = ft_strjoin(pa->var, pa->expanded);
	pa->oper = get_operator(pa->subs, &ret);
	ft_printf("pa list sdfds %s\n", pa->subs);
	ft_printf("pa list  %c\n", pa->flag[0]);
	ft_strdel(&pa->expanded);
	pa->expanded = ft_strnew(1);
	if (pa->oper[0] == ':')
	{
		subs = substitute_or_create(g_sh, pa->subs, &ret);
		temp = ft_strjoin(pa->expanded, subs);
		if (temp == NULL)
			return (1);
		ft_strdel(&pa->expanded);
		pa->expanded = ft_strdup(temp);
		ft_strdel(&subs);
		ft_strdel(&temp);
		// pa->expanded = ft_strupdate(pa->expanded, 
		// substitute_or_create(g_sh, pa->subs, &ret));
	}
	else if (pa->oper[0] == '#' || pa->oper[0] == '%')
	{
		subs = search_from_var(g_sh, pa->subs, &ret);
		if (!subs)
			return (1);
		ft_printf(" subs [%s] \n", subs);
		temp = ft_strjoin(pa->expanded, subs);
		ft_strdel(&pa->expanded);
		pa->expanded = ft_strdup(temp);
		ft_printf(" expanded [%s] \n", pa->expanded);
		ft_strdel(&subs);
		ft_strdel(&temp);
		// pa->expanded = ft_strupdate(pa->expanded, 
		// search_from_var(g_sh, pa->subs, &ret));
	}
	else if (pa->subs[0] == '$' || pa->subs[1] == '#')
	{
		pa->expanded = variable_length(pa->subs);
		ft_printf("%s\n", pa->expanded);
		return (0);
	}
	else
		pa->expanded = ft_expansion_dollar(sh, cmd);
	if (!pa->expanded || !*pa->expanded)
	{
		pa->expanded = ft_strnew(1);
		//ft_printf("42sh: %s: bad substitution\n", cmd);
		// return (-1);
	}
	if (ret == -1)
	{
		ft_strdel(&pa->expanded);
		ft_printf("42sh: %s: bad substitution\n", cmd);
		return (-1);
	}
	ft_printf("pa list alaalla %s\n", pa->expanded);
	return (0);
}

char *separate_form(char *cmd)
{
	char	*fresh;
	int		i;
	int		k;
	int		open;

	i = -1;
	k = 0;
	open = 0;
	fresh = ft_strnew(100);
	while (cmd[++i])
	{
		fresh[k++] = cmd[i];
		if (cmd[i] == '{')
			open += 1;
		else if (cmd[i] == '}')
			open -= 1;
		if (cmd[i] == '}' && open == 0)
		{
			break ;
		}
			
	}
	return (fresh);
}

int	param_format(char **cmd)
{
	int		i;
	int		k;
	int		j;
	int		ret;
	int		err;
	t_param	pa;
	char	*new_cmd;
	char	*subst_cmd;

	err = 0;
	i = -1;
	j = 0;
	new_cmd = NULL;
	while (cmd[++i])
	{
		while (cmd[i][j])  // (check_syntax(cmd[i]))
		{
			k = 0;
			init_pa(&pa);
			//ft_printf("char %c\n", cmd[i][j]);
			ret = 0;
			if (ft_strnequ(&cmd[i][j], "${", 2))
			{
				ft_printf("new\n");
				new_cmd = separate_form(&cmd[i][j]);
				j += ft_strlen(new_cmd);
				ft_printf("start new_cmd %s\n", new_cmd);
			}
			// 	separate_form(&ev_before, &ev_after);
			if (check_syntax(new_cmd))
			{
				if (splits(new_cmd, &pa, &ret) && ret == 0)
				{
					ft_printf("new_cmd %s\n", new_cmd);
					ft_printf("expanded %s %d\n", pa.expanded, ret);
					 ;
				}
				if (ret == 0)
					retoken_into_list(&pa);
				if (expander( &pa, ret))
					err = 1;
				if (ret == 0 && joiner(g_sh, &pa, new_cmd, ret) && ret == 0)
					err = -1;
				if (ret == 1)
				{
					err = -1;
					break ;
				}
				else
				{
					ft_printf("expanded %s %d\n", pa.expanded, ret);
					free_er(&pa, &cmd[i], &subst_cmd, &j);
				}
				
			}
			//ft_strdel(&pa.expanded);
			ft_strdel(&new_cmd);
			if (cmd[i][j])
				j++;
			while (k < 100)
			ft_strdel(&pa.list[k++]);
			free(pa.list);
			ft_strdel(&pa.expanded);
		}
		
		j = 0;
	}
	// while (k < 100)
	// 	ft_strdel(&pa.list[k++]);
	// free(pa.list);
	// ft_strdel(&pa.expanded);
	return (err);
}
