/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:53:08 by spuustin          #+#    #+#             */
/*   Updated: 2023/02/15 22:30:38 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int	cd_multi_command_validation(t_shell *sh, char **commands)
{
	int	ret;

	sh->arr_len = ft_arrlen(commands);
	sh->option = 'e';
	ret = validate_cd_options(sh, commands, 1, 0);
	if ((!commands[1] || ft_strequ(commands[sh->arr_len - 1], "-")) \
	&& sh->arr_len - sh->option_count <= 2)
		return (0);
	if (commands[1][0] == '-' && ret == 1)
	{
		sh->exit_stat = 1;
		return (1);
	}
	if (sh->arr_len - sh->option_count > 2)
	{
		ft_err_print(NULL, "cd", "too many arguments", 2);
		sh->exit_stat = 1;
		return (1);
	}
	return (0);
}

static int	skip_sub_dir(char *path, int i)
{
	int		slashes;

	slashes = 0;
	while (slashes < 2 && i >= 0)
	{
		if (path[i] == '/')
			slashes++;
		i--;
	}
	return (i + 1);
}

void	trim_dot_dot_slash(char *path)
{
	int		i;
	int		idx;
	int		len;

	i = 0;
	while (path[i])
	{
		if (path[i] && path[i + 1] && path[i + 2] && path[i] == '.'
			&& path[i + 1] == '.' && path[i + 2] == '/')
		{
			idx = skip_sub_dir(path, i);
			len = ft_strlen(path + i + 2);
			ft_memmove(&path[idx], &path[i + 2], len);
			path[idx + len] = '\0';
			i = idx;
		}
		i++;
	}
}

char	*trim_dots(char *file, int i)
{
	size_t	post_len;
	char	*path;

	path = ft_strdup(file);
	while (path[i])
	{
		if (path[i] && path[i + 1] && path[i] == '.' && path[i + 1] == '/' \
			&& path[i - 1] && path[i - 1] != '.')
		{
			post_len = ft_strlen(&(path[i]));
			ft_memmove(&path[i], &path[i + 2], post_len);
			path[i + post_len] = '\0';
			i--;
		}
		i++;
	}
	trim_dot_dot_slash(path);
	ft_memdel((void *)&file);
	return (path);
}
