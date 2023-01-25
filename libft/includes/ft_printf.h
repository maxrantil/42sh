/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:22:25 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/17 10:56:59 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdbool.h>

typedef struct flags
{
	int		mod;
	int		hash;
	int		zero;
	int		plus;
	int		minus;
	int		width;
	int		space;
	int		precision;
}				t_flags;

typedef struct arg
{
	va_list	arg;
	char	specifier;
}				t_arg;

typedef struct colours
{
	char	*code;
	char	*name;
}				t_colours;

typedef struct attributes
{
	bool	nan;
	bool	inf;
	bool	zero;
	size_t	padd_len;
	char	*padd;
	char	*width;
	char	*str;
}				t_attr;

bool	precision_util(char *ret, int *precision, int *len, char *str);
char	*str_correction(char *str, t_flags *flags, t_attr *attr, char speci);
char	*di_width_printer(t_flags *flags, char *str, t_attr *attr, char speci);
char	*precision(char *str, int precision, int padd);
char	*padding(t_flags *flags, char *str, char spec, bool zero);
void	attr_init(t_attr *attr);
void	attr_parse(char *str, t_attr *attr, t_flags *flags, char spec);
void	print_date(size_t date, int *ret);
void	non_printa_print(char val, int *ret);
void	ft_bin_print(size_t nbr, int *ret);
char	*coloring(char *format, int *char_count);
int		ft_printf(const char *restrict format, ...);
int		ft_str_convert(char *str, t_flags *flags);
int		ft_char_convert(unsigned int c, t_flags *flags);
int		ft_arg_filter(t_arg *arg, t_flags *flags);
int		ft_diouxf_convert(t_arg *arg, t_flags *flags);
int		ft_printer(char *str, t_flags *flags);
int		ft_diouxf_printer(char *str, t_flags *flags, char specifier);
void	flags_correction(t_flags *flags, char specifier);
int		speci_correction(char specifier);
char	*width_calculator(char *format, t_flags *flags, t_arg *arg);
char	*precision_calculator(char *format, t_flags *flags, t_arg *arg);

#endif
