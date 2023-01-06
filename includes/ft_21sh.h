/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:44:45 by mrantil           #+#    #+#             */
/*   Updated: 2023/01/05 13:48:58 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_21SH_H
# define FT_21SH_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "vec.h"
# include "keyboard.h"
# include <dirent.h>
# include <sys/stat.h>

# if __linux__
#  include <sys/types.h>
#  include <sys/wait.h>
# endif

/* Exec Node */
# define EXEC 1
/* | */
# define PIPE 2
/* > */
# define REDIROVER 3
/* >> */
# define REDIRAPP 4
/* < */
# define REDIRIN 5
/* >& */
# define FILEAGG 6
/* & */
# define AMP 7
/* ; */
# define SEMI 8
/* Tree Print */
# define COUNT 10
/* Hash Table */
# define HASH_SIZE 25
/* Unix */
# define MAX_PATHLEN 1024

# define LOOP 1
# define EXEC_21SH 2
# define END 3

typedef struct s_shell
{
	struct termios	orig_termios;
	struct termios	raw;
	t_vec			v_tmp_env;
	char			**temp_env;
	char			**env;
	char			**paths;
	char			*cl;
	char			*term_name;
}					t_shell;

typedef struct s_node
{
	int				type;
	char			**arg;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

typedef struct s_line
{
	char	*line;
	char	*tok;
	char	*end_q;
	int		type;
	int		fileagg_len;
	int		fd_len;
}			t_line;

typedef struct s_dollar
{
	char	*pre;
	char	*content;
	char	**str;
	char	*post;
	size_t	env_len;
}			t_dollar;

/* Aggregation */
void	check_file_aggregations(t_node *n, t_shell *sh);
int		check_filename_fd(char *filename);
int		check_operator_errors(int old, int file_fd, char *filename, char *oper);
int		open_check(char *filename, int mode);
int		redirect_aggregate(int old_fd, char *target, char *operator);
int		syntax_error_msg(int exit_code);

/* Builtin */
char	*env_getvalue(char **env, char *var);
char	*env_key_extract(char *key_value);
char	**env_underscore(t_node *n, t_shell *sh);
char	**pwd_update(t_shell *sh, char *oldcwd);
void	setenv_loop(t_shell *sh, char *arg, int flag_temp);
char	**setenv_var(char **env, char *key, char *value);
int		sh_cd(t_node *n, t_shell *sh);
int		sh_echo(t_node *n, t_shell *sh);
int		sh_env(t_node *n, t_shell *sh);
int		sh_exit(t_node *n, t_shell *sh);
int		sh_hash(t_node *n, t_shell *sh);
int		sh_setenv(t_node *n, t_shell *sh);
int		sh_unsetenv(t_node *n, t_shell *sh);
char	**unsetenv_var(char **env, char *key);

/* Error */
t_node	*error_redir(t_node *n, char **ptr_to_line);
t_node	*exec_error(t_node *n, int type);
void	sh_error_print(char *arg, int i);

/* Exec */
int		check_paths(t_shell *sh);
int		exec_21sh(t_node *n, t_shell *sh);
void	exec_pipe_node(t_node *n, t_shell *sh);
int		exec_tree(t_node *n, t_shell *sh);
int		fork_wrap(void);
void	input_file_read(t_node *n, t_shell *sh);
void	redirection_file(t_node *n, t_shell *sh);

/* Expansions */
void	expansions_dollar(t_node *n, t_shell *sh, char *dollar, size_t i);
void	expansions_tilde(t_node *n, t_shell *sh, size_t i);
void	expansions(t_node *n, t_shell *sh);
void	fill_env(char **tmp, t_dollar *dol, char *str, t_shell *sh);
ssize_t	find_matching_quote(char *str, char quote);
char	*get_full_env_name(char *var);
void	loop_conversions_quotes(t_node *n, t_shell *sh);
ssize_t	remove_backslash(char *str);
size_t	strip_quotes_double(char **str, size_t quote1, t_shell *sh);
size_t	strip_quotes_single(char *str, size_t quote1);
size_t	update_arg_dollar(int i, char **str, t_shell *sh);

/* Main */
char	*check_heredoc(t_term *t, char *str);
char	**get_env(char **env);
void	init(t_shell *sh, t_term *t);
void	print_banner(void);

/* Parser */
void	add_to_args(char ***array, char *str);
int		exec_is_quote_somewhere(char *tok);
void	look_for_redir(t_line *l, char **ptr_to_line);
void	mv_tok_and_line(char **tok, char ***ptr_to_line, int len);
t_node	*node_create(int type, t_node *left, t_node *right);
t_node	*parse_exec(t_line *l, char **ptr_to_line);
t_node	*parse_line(t_line *l, char **ptr_to_line);
t_node	*parse_pipe(t_line *l, char **ptr_to_line);
t_node	*parse_redirection(t_node *n, t_line *l, char **ptr_to_line);
int		peek(char **ptr_to_line, char *toks);
void	redir_node_add_args(t_node *n, char ***ptr_to_line, \
char **tok, int len);
int		tok_get(char **ptr_to_line, char **tok, char **end_q);

/* Utils */
int		dup2_wrap(int file_fd, int old_fd);
void	free_mem(t_node *n, t_shell *sh, ssize_t code);
void	ft_disable_raw_mode(t_shell *sh);
void	ft_enable_raw_mode(t_shell *sh);
void	reset_fds(char *term_name);
void	tree_free(t_node *n);
void	tree_print(t_node *root);

typedef int				(*t_fptr)(t_node *n, t_shell *sh);

static const char		*g_builtin_str[] = {
	"cd",
	"echo",
	"env",
	"exit",
	"setenv",
	"unsetenv"
};

static const t_fptr		g_builtin_func[] = {
	&sh_cd,
	&sh_echo,
	&sh_env,
	&sh_exit,
	&sh_setenv,
	&sh_unsetenv
};

#endif
