/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 20:04:51 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/18 12:04:02 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static char	*get_command(char *str, size_t i, size_t len_ndle)
{
	char	*ret;
	char	*pre_ndle;
	char	*post_ndle;

	post_ndle = NULL;
	pre_ndle = ft_strsub(str, 0, i);
	if (ft_strlen(str) > (i + len_ndle))
	{
		post_ndle = ft_strsub(str, i + len_ndle, \
		ft_strlen(str) - (i + len_ndle));
		ret = ft_strjoin(pre_ndle, "/tmp/heredoc");
		ret = strjoin_head(ret, post_ndle);
		ft_strdel(&post_ndle);
	}
	else
		ret = ft_strjoin(pre_ndle, "/tmp/heredoc");
	ft_strdel(&pre_ndle);
	ft_strdel(&str);
	return (ret);
}

static char	*change_delim_to_file(t_term *t, char *str)
{
	size_t	i;
	size_t	len_ndle;

	i = 0;
	len_ndle = ft_strlen(t->delim);
	while (str && str[i])
	{
		if (!ft_strnequ(&str[i], t->delim, len_ndle))
			i++;
		else
			break ;
	}
	ft_strdel(&t->delim);
	if (str && str[i])
		return (get_command(str, i, len_ndle));
	return (NULL);
}

static char	*make_heredoc_input(t_term *t, char *str)
{
	size_t	len;
	int		i;

	i = 0;
	while (str && str[i])
	{
		if (i && str[i] == '<' && str[i - 1] == '<')
		{
			len = ft_strlen(&str[i]);
			ft_memmove((void *)&str[i], (void *)&str[i + 1], len);
		}
		i++;
	}
	return (change_delim_to_file(t, str));
}

static char	*write_to_tmp_file(t_term *t, char *str, int fd)
{
	char	*ret;
	char	*cpy;

	ret = ft_strsub(str, 0, ft_strchr(str, '\n') - str);
	cpy = ft_strchr(str, '\n') + 1;
	if (ft_strrchr(cpy, '\n'))
		cpy = ft_strsub(cpy, 0, (ft_strrchr(cpy, '\n') - cpy) + 1);
	if (*cpy && !ft_strequ(cpy, t->delim))
	{
		write(fd, cpy, ft_strlen(cpy));
		ft_strdel(&cpy);
	}
	else
		write(fd, "\0", 1);
	ft_strdel(&str);
	close(fd);
	return (make_heredoc_input(t, ret));
}

char	*ft_heredoc(t_term *t, char *str)
{
	int		fd;

	if (t->heredoc)
	{
		fd = open("/tmp/heredoc", O_RDWR | O_CREAT | O_TRUNC, 0755);
		if (fd)
			return (write_to_tmp_file(t, str, fd));
		else
			ft_strdel(&t->delim);
	}
	return (str);
}
