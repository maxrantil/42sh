/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:40:05 by mviinika          #+#    #+#             */
/*   Updated: 2023/02/23 13:16:56 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	check_syntax(char *cmd)
{
	int	len;

	if (!cmd)
		return (0);
	len = ft_strlen(cmd) - 1;
	if (ft_strnequ(cmd, "${", 2) && cmd[len] == '}')
		return (1);
	return (0);
}

static char	*separate_form(char *cmd)
{
	char	*fresh;
	int		i;
	int		k;
	int		open;

	i = -1;
	k = 0;
	open = 0;
	fresh = ft_strnew(ft_strlen(cmd));
	while (cmd[++i])
	{
		fresh[k++] = cmd[i];
		if (cmd[i] == '{')
			open += 1;
		else if (cmd[i] == '}')
			open -= 1;
		if (cmd[i] == '}' && open == 0)
			break ;
	}
	return (fresh);
}

static char	*init_form_cycle(t_param *pa, char *cmd, t_pa_ints *ints)
{
	char	*new_cmd;
	char	check;

	init_pa(pa);
	ints->ret = 0;
	check = '\0';
	if (ints->j >= 1)
		check = cmd[ints->j - 1];
	new_cmd = NULL;
	if (ft_strnequ(&cmd[ints->j], "${", 2) && check != '\\' && check != '\'')
	{
		new_cmd = separate_form(&cmd[ints->j]);
		ints->j += ft_strlen(new_cmd);
	}
	return (new_cmd);
}

static int	proceed_to_execute(t_param *pa, \
		t_pa_ints *ints, char **cmd, int *ret)
{
	char	*new_cmd;

	new_cmd = init_form_cycle(pa, cmd[ints->i], ints);
	if (check_syntax(new_cmd))
	{
		*ret = perform_param_expans(new_cmd, pa, &ints->ret);
		substitute_og_cmd(pa, &cmd[ints->i], &ints->j);
		if (*ret != 0)
		{
			free_attrs(pa, &new_cmd);
			if (ints->ret == -1 || *ret == -2)
				return (-1);
			return (1);
		}
	}
	ints->j++;
	free_attrs(pa, &new_cmd);
	return (0);
}

int	param_format(char **cmd)
{
	t_param		pa;
	t_pa_ints	ints;
	int			ret;

	init_pa_ints(&ints);
	while (cmd[++ints.i])
	{
		while (cmd[ints.i][ints.j])
		{
		//ft_printf("cmd[ints.i] %s\n", cmd[ints.i]);
			ret = proceed_to_execute(&pa, &ints, cmd, &ret);
			if (ret == -1)
				return (-1);
			if (ints.j > (int)ft_strlen(cmd[ints.i]))
				break ;
		}
		ints.j = 0;
		//trim_and_remove_null(&cmd, &ints);
		//ft_printf("ju cmd[ints.i] %s\n", cmd[ints.i]);
	}
	return (ints.err);
}
