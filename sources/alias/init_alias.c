/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_alias.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 20:06:04 by rvuorenl          #+#    #+#             */
/*   Updated: 2023/02/16 12:34:45 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

//	parse command from line, add quotes to command if missing, return to array
static char	*format_alias(char *line)
{
	int		i;
	char	*command;
	char	*content;
	char	*alias;

	i = skip_to_second_word(line);
	command = get_alias_command(&(line[i]));
	remove_quotes_cmd(command);
	content = get_alias_content(&(line[i]));
	add_quotes(&content);
	alias = ft_strjoin_three(command, "=", content);
	ft_strdel(&command);
	ft_strdel(&content);
	return (alias);
}

static void	fill_alias_array(char *file, char **alias, int file_fd)
{
	int		fd;
	int		i;
	char	*line;

	close(file_fd);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("ERROR opening file \'%s\'\n", file);
		exit(1);
	}
	else
	{
		i = 0;
		while (get_next_line(fd, &line) > 0)
		{
			if (ft_strncmp(line, "alias", 5) == 0)
			{
				if (validate_alias(&(line[6]), 0))
					alias[i++] = format_alias(line);
			}
			ft_strdel(&line);
		}
	}
}

static int	count_aliases_rcfile(int alias_file)
{
	char	*line;
	int		alias_count;

	alias_count = 0;
	while (get_next_line(alias_file, &line) > 0)
	{
		if (ft_strncmp(line, "alias", 5) == 0)
		{
			if (validate_alias(&(line[6]), 0))
				alias_count++;
		}
		ft_strdel(&line);
	}
	return (alias_count);
}

static char	**create_alias_array(int file_fd, char *filename, t_shell *sh)
{
	char	**alias;

	sh->alias_size = count_aliases_rcfile(file_fd);
	alias = ft_create_empty_str_array(sh->alias_size);
	if (sh->alias_size > 0)
		fill_alias_array(filename, alias, file_fd);
	return (alias);
}

void	init_alias(t_shell *sh)
{
	char	*home_var;
	char	*rc_filename;
	int		rcfile_fd;

	home_var = ft_strchr(*ft_env_get(sh, "HOME", sh->env), '=') + 1;
	rc_filename = ft_strjoin(home_var, "/.bashrc");
	rcfile_fd = open(rc_filename, O_RDONLY);
	sh->alias = create_alias_array(rcfile_fd, rc_filename, sh);
	close(rcfile_fd);
	ft_strdel(&rc_filename);
}
