/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_addr_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 18:27:40 by mbarutel          #+#    #+#             */
/*   Updated: 2023/01/06 12:52:59 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/**
 * It checks if the file is a directory and if it has the right permissions
 * 
 * @param file the file to check
 */
int	ft_cd_addr_check(char *file)
{
	struct stat	buff;

	if (stat(file, &buff))
		return (ft_err_print(file, "cd", "No such file or directory", 1));
	else
	{
		if (!S_ISDIR(buff.st_mode))
			return (ft_err_print(file, "cd", "Not a directory", 1));
		else if (access(file, X_OK))
			return (ft_err_print(file, "cd", "Permission denied", 1));
	}
	return (0);
}
