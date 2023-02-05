/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spuustin <spuustin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:53:08 by spuustin          #+#    #+#             */
/*   Updated: 2023/02/05 19:47:37 by spuustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

//add to libft
static char	*ft_strjoin_three(char *s1, char *s2, char *s3)
{
	size_t	total;
	char	*new;

	if (!s1 || !s2 || !s3)
		return (NULL);
	total = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	new = ft_strnew(total);
	if (new != NULL)
	{
		new = ft_strcpy(new, (const char *)s1);
		new = ft_strcat(new, (const char *)s2);
		new = ft_strcat(new, (const char *)s3);
	}
	return (new);
}

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

int	cd_multi_command_validation(t_session *sesh, char **commands)
{
	if (commands[1][0] != '-')
	{
		ft_err_print(NULL, "cd", "too many arguments", 1);
		sesh->exit_stat = 1;
		return (1);
	}
	if (validate_cd_options(sesh, commands, 1, 0) == 1)
	{
		sesh->exit_stat = 1;
		return (1);
	}
	return (0);
}
