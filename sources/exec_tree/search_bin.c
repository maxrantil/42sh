/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 18:01:29 by jniemine          #+#    #+#             */
/*   Updated: 2022/12/19 16:16:00 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	ft_memd_w(void **ap)
{
	if (!ap || !(*ap))
		return (1);
	ft_memdel(ap);
	return (1);
}

static int	ft_freeda_w(void ***a, size_t row)
{
	ft_freeda(a, row);
	return (1);
}

static char	*search_variable(char **environ_cp, char *var_name)
{
	int		i;
	char	*var_value;
	int		len;

	i = 0;
	len = ft_strlen(var_name);
	var_value = NULL;
	while (environ_cp[i]
		&& !(ft_strnequ(environ_cp[i], var_name, len)
			&& environ_cp[i][len] == '='))
		++i;
	if (environ_cp[i] && environ_cp[i][len] == '=')
	{
		var_value = ft_strdup(ft_strchr(environ_cp[i], '=') + 1);
		if (!var_value)
			error_exit("Malloc fail\n");
	}
	return (var_value);
}

static int	try_cmd(char **cmd, char **environ_cp, char **temp_path)
{
	if (!access(*cmd, F_OK) && !access(*cmd, X_OK))
	{
		if (ft_strchr(*cmd, '/'))
			return (1);
	}
	*temp_path = search_variable(environ_cp, "PATH");
	return (0);
}

char	*search_bin(char *cmd, char **environ_cp)
{
	char	**bin_paths;
	char	*temp_path;
	char	*exepath;
	int		i;

	i = -1;
	if (try_cmd(&cmd, environ_cp, &temp_path))
		return (ft_strdup(cmd));
	if (temp_path)
	{
		bin_paths = ft_strsplit(temp_path, ':');
		while (ft_memd_w((void **)&temp_path) && bin_paths && bin_paths[++i])
		{
			temp_path = ft_strjoin(bin_paths[i], "/");
			exepath = ft_strjoin(temp_path, cmd);
			if (ft_memd_w((void **)&temp_path) && !access(exepath, F_OK)
				&& !access(exepath, X_OK)
				&& ft_freeda_w((void ***)&bin_paths, calc_chptr(bin_paths)))
				return (exepath);
			else
				ft_memdel((void **)&exepath);
		}
		ft_freeda((void ***)&bin_paths, calc_chptr(bin_paths));
	}
	return (NULL);
}
