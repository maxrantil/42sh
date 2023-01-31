/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:15:33 by jniemine          #+#    #+#             */
/*   Updated: 2023/01/31 16:16:00 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	init_params(char *line, t_token **args, size_t *pointer_n)
{
	if (!line || !*line)
		return (1);
	*pointer_n = 1;
	*args = ft_memalloc(sizeof(**args) * 2);
	(*args)[0].token = 0;
	(*args)[1].token = 0;
	return (0);
}

static void	init_variables(int *i_args, int *cur, int *start, int *end)
{
	*i_args = 0;
	*cur = 0;
	*start = 0;
	*end = 0;
}

static int	if_error(char *c, t_token *args, char *line, int *end)
{
	if (!c || test_if_error(&line[*end]))
	{
		free_tokens(&args);
		ft_strdel(&line);
		if (c)
			ft_strdel(&c);
		return (1);
	}
	return (0);
}

static int	validity_check(char *line)
{
	char	*ptr;

	ptr = NULL;
	if (*line == ';' || *line == '|' || *line == '&')
		ptr = line;
	else if (line[ft_strlen(line) - 1] == '|')
		ptr = &line[ft_strlen(line) - 1];
	if (ptr)
	{
		ft_putstr_fd("42sh: syntax error near unexpected token `", 2);
		write(2, ptr, 1);
		ft_putstr_fd("'\n", 2);
		ft_strdel(&line);
		return (1);
	}
	return (0);
}

t_token	*chop_line(char *line, t_token *args, size_t pointer_n)
{
	int		i_args;
	char	*c;
	int		cur;
	int		start;
	int		end;

	if (!line || validity_check(line) || init_params(line, &args, &pointer_n))
		return (NULL);
	init_variables(&i_args, &cur, &start, &end);
	while (line[cur])
	{
		c = find_argument(line, &cur, &start, &end);
		if (if_error(c, args, line, &end))
			return (NULL);
		init_token(c, &args[i_args], line, cur);
		++i_args;
		track_used_space(&args, i_args, &pointer_n);
		while (ft_isspace(line[end]))
			++end;
		cur = end;
		while (ft_isspace(line[cur]))
			++cur;
	}
	// print_tokens(args);
	ft_strdel(&line);
	return (args);
}
