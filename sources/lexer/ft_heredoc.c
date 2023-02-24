/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 20:04:51 by mbarutel          #+#    #+#             */
/*   Updated: 2023/02/24 18:35:52 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static char	*make_heredoc_input(char *str)
{
	ft_strclr(ft_strrchr(str, '<'));
	return (strjoin_head(str, " /tmp/heredoc"));
}

static void	get_to_end_of_delim(t_term *t, char **cpy)
{
	char	*ptr;

	ptr = t->delim;
	while (*(*cpy))
	{
		if (*(*cpy) == *ptr)
			ptr++;
		(*cpy)++;
		if (!*ptr)
			break ;
	}
}

static char	*write_to_tmp_file(t_term *t, char *str, int fd)
{
	char	*ret;
	char	*cpy;

	ret = ft_strsub(str, 0, ft_strchr(str, '\n') - str);
	cpy = ft_strchr(str, '<') + 1;
	get_to_end_of_delim(t, &cpy);
	if (ft_strrchr(cpy, '\n'))
		cpy = ft_strsub(ft_strchr(cpy, '\n') + 1, 0, \
		((ft_strrchr(cpy, '\n') - 1) - ft_strchr(cpy, '\n') + 1));
	if (cpy && !ft_strequ(cpy, t->delim))
	{
		write(fd, cpy, ft_strlen(cpy));
		ft_strdel(&cpy);
	}
	else
		write(fd, "\0", 1);
	ft_strdel(&t->delim);
	ft_strdel(&str);
	close(fd);
	return (make_heredoc_input(ret));
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
