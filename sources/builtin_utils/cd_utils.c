/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:53:08 by spuustin          #+#    #+#             */
/*   Updated: 2023/02/06 12:14:13 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	build_trimmed(char **trimmed, char *src)
{
	char	*temp;

	if (!*trimmed)
			*trimmed = ft_strjoin("/", src);
	else
	{
		temp = *trimmed;
		*trimmed = ft_strjoin_three(*trimmed, "/", src);
		ft_memdel((void *)&temp);
	}
}

char	*trim_dots_helper(char **arr, char *trimmed, int i, int to_skip)
{
	while (arr[i])
	{
		while (ft_strequ(arr[i], ".") || \
		(arr[i + 1] && ft_strequ(arr[i + 1], "..")))
		{
			if (ft_strequ(arr[i + 1], ".."))
					to_skip++;
			i++;
		}
		i += to_skip;
		if (arr[i] && !ft_strequ(arr[i], "..") && !ft_strequ(arr[i], "."))
		{
			build_trimmed(&trimmed, arr[i]);
		}
		to_skip = 0;
		i++;
	}
	return (trimmed);
}

int	cd_multi_command_validation(t_shell *sh, char **commands)
{
	if (commands[1][0] != '-')
	{
		ft_err_print(NULL, "cd", "too many arguments", 1);
		sh->exit_stat = 1;
		return (1);
	}
	if (validate_cd_options(sh, commands, 1, 0) == 1)
	{
		sh->exit_stat = 1;
		return (1);
	}
	return (0);
}
