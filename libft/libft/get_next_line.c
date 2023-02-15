/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 12:27:25 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/07 14:59:50 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	join_str(char *tmp, char **files)
{
	char	*copy;

	copy = ft_strdup(*files);
	if (!copy)
		return (-1);
	ft_strdel(files);
	*files = ft_strjoin(copy, tmp);
	free(copy);
	if (!*files)
		return (-1);
	return (0);
}

static int	sub_move(char **files, char **line, size_t i)
{
	*line = ft_strsub(*files, 0, i);
	if (!*line)
		return (-1);
	ft_strcpy(*files, *files + i + 1);
	return (1);
}

static int	check_buf(char **files, char **line, int res)
{
	size_t	i;

	i = 0;
	while (*(*files + i))
	{
		if (*(*files + i) == '\n')
			return (sub_move(files, line, i));
		i++;
	}
	if (res == 0)
	{
		if (i > 0)
		{
			*line = ft_strdup(*files);
			if (!*line)
				return (-1);
			ft_strdel(files);
			return (1);
		}
		else
			return (0);
	}
	return (2);
}

static int	check_args(char **line, char **files, int res_buf, char *tmp)
{
	int	res_check;

	if (res_buf == 0 && !*files)
		return (res_buf);
	if (*files && res_buf != 0)
	{
		res_check = join_str(tmp, files);
		if (res_check == -1)
			return (res_check);
	}
	else if (!*files && res_buf != 0)
	{
		*files = ft_strdup(tmp);
		if (!*files)
			return (-1);
	}
	ft_strclr(tmp);
	res_check = check_buf(files, line, res_buf);
	return (res_check);
}

int	get_next_line(const int fd, char **line)
{
	static char	*files[4096];
	char		tmp[BUFF_SIZE + 1];
	int			res_buf;
	int			res_check;

	if (BUFF_SIZE <= 0 || fd > 4096 || !line || fd < 0)
		return (-1);
	res_buf = read(fd, tmp, BUFF_SIZE);
	while (res_buf != -1)
	{
		tmp[res_buf] = '\0';
		res_check = check_args(line, &files[fd], res_buf, tmp);
		if (res_check != 2)
			return (res_check);
		res_buf = read(fd, tmp, BUFF_SIZE);
	}
	return (-1);
}
