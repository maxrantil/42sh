/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/01/25 15:00:17 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_21sh.h"

#include "ft_21sh.h"

/*
 * It reads the history file and stores it in a ft_vector
 *
 * @param t the terminal structure
 */
static void	count_history(t_term *t, int *x)
{
	int		fd;
	char	*line;

	t->history_size = 0;
	fd = open(t->history_file, O_RDONLY | O_CREAT, 420);
	if (fd)
	{
		line = NULL;
		while (get_next_line(fd, &line) > 0)
		{
			t->history_size++;
			ft_strdel(&line);
		}
		ft_strdel(&line);
		close(fd);
	}
	if (t->history_size > MAX_HISTORY)
	{
		*x = t->history_size;
		t->history_size = MAX_HISTORY;
	}
}

static char	*ft_history_get_file(char *str)
{
	char	cwd[BUFF_SIZE];
	char	*home;
	char	*file;

	home = getenv("HOME");
	if (home)
		return (ft_strjoin(home, str));
	file = getcwd(cwd, sizeof(cwd));
	return (ft_strjoin(file, str));
}

static void	get_loop(t_term *t, int x)
{
	int		i;
	int		fd;
	char	*line;

	fd = open(t->history_file, O_RDONLY | O_CREAT, 420);
	if (fd)
	{
		line = NULL;
		i = 0;
		while (get_next_line(fd, &line) > 0)
		{
			if (x-- > MAX_HISTORY)
			{
				ft_strdel(&line);
				continue ;
			}
			t->history_arr[i++] = ft_strdup(line);
			ft_strdel(&line);
		}
		ft_strdel(&line);
		close(fd);
		t->history_arr[i] = NULL;
		t->history_size = i;
	}
}

void	ft_history_get(t_term *t)
{
	int		x;

	t->history_file = ft_history_get_file("/.42sh_history");
	x = 0;
	count_history(t, &x);
	t->history_arr = (char **)malloc(sizeof(char *) * (t->history_size + 1));
	ft_bzero(t->history_arr, t->history_size + 1);
	get_loop(t, x);
}
