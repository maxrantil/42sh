/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:51:26 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/20 11:04:24 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYBOARD_H
# define KEYBOARD_H

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include "vec.h"
# include <termcap.h>
# include <termios.h>
# include <fcntl.h>
# include <sys/ioctl.h>

# if __linux__
#  include <term.h>
#  include <curses.h>
#  include <signal.h>
#  include <limits.h>
#  include <ctype.h>
# endif

# define DEL		0
# define BCK		1
# define ENTER      10
# define CTRL_C		3
# define CTRL_D		4
# define CTRL_L		12
# define CTRL_W		23
# define CTRL_U		21
# define CTRL_Y		25
# define D_QUO		34
# define S_QUO		39
# define ESCAPE     27
# define LINE_MV    49
# define KEY_SHIFT  50
# define ARROW_UP   65
# define ARROW_DOWN	66
# define ARROW_LFT	67
# define ARROW_RGHT	68
# define CURS_END	70
# define CURS_BIGIN	72
# define ALT_LFT	98
# define ALT_RGHT	102
# define DOWN		261
# define UP			262
# define LEFT       263
# define RIGHT      264
# define BACKSPACE	127
# define TAB		9
# define COPY		0
# define CUT		1

# define PROMPT "$> "
# define MINI_PROMPT "> "

# define BUFFSIZE   2048 //control the buffsize so that works fine
# define MAX_LINE   1024

typedef struct clipboard
{
	int		type;
	char	*buff;
}			t_clipboard;

typedef struct s_term
{
	char			inp[BUFFSIZE];
	char			history_buff[BUFFSIZE];
	t_vec			v_history;
	t_clipboard		clipboard;
	char			**nl_addr;
	char			*history_file;
	char			*input_cpy;
	char			*delim;
	int				ch;
	int				history_row;
	ssize_t			ws_col;
	ssize_t			ws_row;
	ssize_t			index;
	ssize_t			bytes;
	ssize_t			start_row;
	ssize_t			c_col;
	ssize_t			c_row;
	ssize_t			total_row;
	ssize_t			total_row_cpy;
	ssize_t			prompt_len;
	ssize_t			m_prompt_len;
	ssize_t			q_qty;
	ssize_t			bslash;
	ssize_t			heredoc;
	ssize_t			his;
	ssize_t			sigint;
	char			quote;
}			t_term;

void	ft_add_nl_last_row(t_term *t, char *array, ssize_t pos);
void	ft_add_nl_mid_row(t_term *t, ssize_t row, ssize_t pos);
void	ft_alt_mv(t_term *t);
void	ft_arrow_input(t_term *t);
void	ft_backspace(t_term *t);
int		ft_bslash_escape_check(t_term *t, ssize_t pos);
void	ft_copy(t_term *t);
void	ft_create_prompt_line(t_term *t, ssize_t loc);
void	ft_cut(t_term *t);
void	ft_delete(t_term *t);
void	ft_deletion_shift(t_term *t, ssize_t index);
int		ft_delim_fetch(t_term *t);
void	ft_end_cycle(t_term *t);
void	ft_esc_parse(t_term *t);
int		ft_get_input(void);
ssize_t	ft_get_prompt_len(t_term *t, ssize_t row);
int		ft_get_linenbr(void);
void	ft_heredoc_handling(t_term *t, int index);
void	ft_history(t_term *t);
char	*ft_history_file_get(void);
void	ft_history_get(t_term *t);
void	ft_history_reset_nl(t_term *t, char *inp);
void	ft_history_write_to_file(t_term *t);
void	ft_history_trigger(t_term *t, ssize_t his);
void	ft_init(t_term *t);
void	ft_init_term(t_term *t);
void	ft_init_signals(void);
int		ft_input_cycle(t_term *t);
void	ft_insertion(t_term *t);
char	*ft_is_prompt_line(t_term *t, ssize_t row);
ssize_t	ft_len_lowest_line(t_term *t, ssize_t row);
void	ft_line_down(t_term *t);
void	ft_line_mv(t_term *t);
void	ft_line_up(t_term *t);
ssize_t	ft_mv_prompt_len(t_term *t, int num);
void	ft_nl_removal(t_term *t);
void	ft_paste(t_term *t);
void	ft_print_input(t_term *t, ssize_t row, int mode);
void	ft_print_trail(t_term *t);
int		ft_putc(int c);
void	ft_quote_decrement(t_term *t, ssize_t index);
void	ft_quote_flag_check(t_term *t, ssize_t index);
void	ft_quote_flag_reset(t_term *t);
void	ft_quote_handling(t_term *t, char ch);
void	ft_remove_nl_addr(t_term *t, ssize_t row);
void	ft_reset_nl_addr(t_term *t);
void	ft_restart_cycle(t_term *t);
ssize_t	ft_row_lowest_line(t_term *t);
void	ft_run_capability(char *cap);
void	ft_setcursor(ssize_t col, ssize_t row);
void	ft_shift_insert(t_term *t);
void	ft_shift_nl_addr(t_term *t, int num);
void	ft_trigger_nl(t_term *t);
void	ft_window_size(t_term *t);
void	ft_word_mv(t_term *t);

#endif
