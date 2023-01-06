/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 15:06:19 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/14 11:38:29 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

# define SPECIF "cspdiouxXfb%"
# define FLAGS "+-#0 "
# define PF_COLORS "nrgybmcw"
# define LENGTH "hhllL"
# define NOR  "\x1B[0;0m"
# define RED  "\x1B[0;31m"
# define GRE  "\x1B[0;32m"
# define YEL  "\x1B[0;33m"
# define BLU  "\x1B[0;34m"
# define MAG  "\x1B[0;35m"
# define CYA  "\x1B[0;36m"
# define WHI  "\x1B[0;37m"

typedef struct s_ftprintf
{
	va_list				ap;
	const char			*fmt;
	int					space_count;
	ssize_t				char_count;
	size_t				astx_flag;
	size_t				len_va_arg;
	int					plus_flag;
	int					minus_flag;
	size_t				width;
	size_t				width_check;
	size_t				precision;
	long long			va_ret;
	unsigned long long	va_u_ret;
	int					hash_flag;
	size_t				zero;
	int					zero_flag;
	char				*hold_str;
	int					le_f;
	int					for_plus;
	int					precision_flag;
	int					uint_check;
	int					sign;
}						t_ftprintf;

/*
** Functions for print dispatch table
*/

void	int_print(t_ftprintf *data);
void	char_print(t_ftprintf *data);
void	str_print(t_ftprintf *data);
void	uint_print(t_ftprintf *data);
void	oct_print(t_ftprintf *data);
void	hex_print(t_ftprintf *data);
void	address_print(t_ftprintf *data);
void	float_print(t_ftprintf *data);
void	asterix_print(t_ftprintf *data);
void	binary_print(t_ftprintf *data);
void	print_procent(t_ftprintf *data);
void	null_print(t_ftprintf *data);

/*
** Functions for flags dispatch table
*/

void	flag_plus(t_ftprintf *data);
void	flag_minus(t_ftprintf *data);
void	procentage_print(t_ftprintf *data);
void	get_flag_space(t_ftprintf *data);
void	exec_flag_space(t_ftprintf *data);
void	hash_flag(t_ftprintf *data);
void	get_flag_zero(t_ftprintf *data);
void	exec_flag_zero(t_ftprintf *data);
void	null_flag(t_ftprintf *data);

/*
** check width and precision functions
*/

void	check_width(t_ftprintf *data);
void	exec_width(t_ftprintf *data);
void	check_precision(t_ftprintf *data);
void	exec_precision(t_ftprintf *data);
void	check_signed_length(t_ftprintf *data);
void	check_unsigned_length(t_ftprintf *data);
void	check_hex_length(t_ftprintf *data);
void	check_oct_length(t_ftprintf *data);

/*
** Other functions
*/

int		ft_printf(const char *fmt, ...);
void	check_parser(t_ftprintf *data);
void	pf_putint(t_ftprintf *data);
size_t	get_it(t_ftprintf *data);
char	*conv_to_str(long long nbr, t_ftprintf *data);
char	*uint_str(unsigned long long nbr, t_ftprintf *data);
void	pf_print_hex_hash(t_ftprintf *data);
void	pf_write_o(t_ftprintf *data);
void	conv_float_str(long double nbr, t_ftprintf *data);
void	ignore_zero_flag(t_ftprintf *data);

/*
** Tools
*/

void	pf_write(t_ftprintf *data);
void	itoa_b(unsigned long long nbr, unsigned int base, t_ftprintf *data);
void	pf_exec_before_flags(t_ftprintf *data);
void	exec_flags_and_length(t_ftprintf *data);
void	write_colors(t_ftprintf *data);

typedef void					(*t_fptr_print_op)(t_ftprintf *data);
typedef void					(*t_fptr_flag_op)(t_ftprintf *data);
typedef void					(*t_fptr_check_op)(t_ftprintf *data);

static const t_fptr_print_op	g_print_disp_tbl[13] = {
	char_print,
	str_print,
	address_print,
	int_print,
	int_print,
	oct_print,
	uint_print,
	hex_print,
	hex_print,
	float_print,
	binary_print,
	print_procent,
	null_print,
};

static const t_fptr_flag_op		g_flag_disp_tbl[6] = {
	flag_plus,
	flag_minus,
	hash_flag,
	get_flag_zero,
	get_flag_space,
	null_flag,
};

static const t_fptr_check_op	g_check_disp_tbl[6] = {
	check_width,
	check_precision,
	check_signed_length,
	check_unsigned_length,
	check_hex_length,
	check_oct_length,
};

#endif
