/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_42sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/02/15 20:39:49 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_42SH_H
# define FT_42SH_H

# include "libft.h"
# include "keyboard.h"
# include "ft_printf.h"
# include <sys/stat.h>
# include <sys/shm.h>
# include <signal.h>
# include <dirent.h>
# include <fcntl.h>
# include <pwd.h>

# if __gnu_linux__
#  include <fcntl.h>
# endif
# if __linux__
#  include <wait.h>
#  include <sys/types.h>
#  include <sys/wait.h>
# endif

/* Do not use zero */
# define PIPE 1
# define CMD 2
# define REDIR 3
# define WORD 4
# define SEMICOLON 5
# define AMPERSAND 6
# define AGGREGATION 7
# define CLOSEFD 8
# define SKIP_TOK 9
# define LOGICAL_AND 10
# define LOGICAL_OR 11

/* For error messages */
# define SHELL_NAME "42sh"

/* limit for filedescriptors */
# define SH_FD_MAX 255

/* Limit for jobs */
# define JOBS_MAX 255

/* Hash Table */
# define HASH_SIZE 25

/* Build tree, redir types */
# define RE_IN_ONE 1
# define RE_IN_TWO 2
# define RE_IN_TRI 3
# define RE_OUT_ONE 4
# define RE_OUT_TWO 5

/* For fc builtin */
# define FC_FLAGS "srnl"
# define FC_LEN 17
# define SH_PATH_MAX 2048
// # define PATH_MAX 2048

/* Jobs States */
# define RUNNING 1
# define STOPPED 2
# define DONE 3
# define TERMINATED 4
# define SUSPENDED 5
# define EXITED 6

/* For print_tree */
# define COUNT 10

/* Parameter expansions */
# define USE_DEFAULT 0
# define ASSIGN_DEFAULT 1
# define DISPLAY_ERR 2
# define ALTERNATE_VALUE 3
# define GET_VALUE ':'
# define SUBSTRING_BEGIN '#'
# define SUBSTRING_END '%'
# define STRING_LEN "$#"

typedef union u_treenode	t_treenode;

/*		       	   TOKENIZER FLAGS				*/
typedef struct s_token_flags
{
	char	quote;
	char	braces;
	int		braces_count;
}				t_token_flags;

/*			PARAMETER EXPANSION INTEGERS		*/
typedef struct s_pa_ints
{
	int	i;
	int	j;
	int	ret;
	int	err;
}	t_pa_ints;

/*			PARAMETER EXPANSION SUBSTRING	*/
typedef struct s_sub
{
	char	*expanded;
	char	*needle;
	char	*haystack;
	char	op[3];
	char	*strip;
	char	*temp_sub;
	char	*temp_hays;
}	t_sub;

/*					TOKEN STRUCT			*/
typedef struct s_token
{
	int		token;
	char	*value;
}	t_token;

/*					SEMICOLON STRUCT		*/
typedef struct s_semicolon
{
	int			type;
	t_treenode	*left;
	t_treenode	*right;
}	t_semicolon;

/*					AMPERSAND NODE			*/
typedef struct s_ampersand
{
	int			type;
	t_treenode	*left;
	t_treenode	*right;
}	t_ampersand;

/*					LOGICAL NODE			*/
typedef struct s_logicalop
{
	int			type;
	t_treenode	*left;
	t_treenode	*right;
}	t_logicalop;

/*					CMD STRUCT				*/
typedef struct s_cmdnode
{
	int		type;
	int		redir_out;
	char	**cmd;

}	t_cmdnode;

/*					CLOSEFD STRUCT			*/
typedef struct s_closefd
{
	int			type;
	int			close_fd;
	t_treenode	*cmd;
}	t_closefd;

/*					REDIR STRUCT			*/
typedef struct s_redir
{
	int			type;
	t_treenode	*cmd;
	int			close_fd;
	char		*filepath;
	int			open_flags;
	int			rights;
}				t_redir;

/*		     AGGREGATION	STRUCT	       	*/
typedef struct s_aggregation
{
	int			type;
	t_treenode	*cmd;
	int			close_fd;
	char		*dest;
}	t_aggregate;

/*				PIPE STRUCT				    */
typedef struct s_pipenode
{
	int			type;
	t_treenode	*left;
	t_treenode	*right;
}	t_pipenode;

/*				PARAM STRUCT				    */
typedef struct s_param
{
	char	**list;
	char	*expanded;
	char	*var;
	char	*subs;
	char	*strip;
	char	*flag;
	char	op;
	char	*oper;
}	t_param;

/*					TREE UNION				*/
union u_treenode
{
	int			type;
	t_redir		redir;
	t_closefd	closefd;
	t_cmdnode	cmd;
	t_pipenode	pipe;
	t_semicolon	semicolon;
	t_aggregate	aggregate;
	t_logicalop	logicalop;
	t_ampersand	ampersand;
};

/*					FC STRUCT			*/
typedef struct s_fc
{
	char	**filename;
	char	*ret_cmd;
	int		start;
	int		end;
	int		flags;
	bool	e;
	bool	s;
	bool	r;
	bool	n;
	bool	l;
}			t_fc;

/*					HASH					*/
typedef struct s_hash
{
	char			*program;
	char			*path;
	int				hits;
	struct s_hash	*next;
}					t_hash;

/*			FOREGROUND JOB NODES				*/
typedef struct s_fg_job
{
	pid_t	gpid;
	pid_t	*pid;
	char	***cmd;
}			t_fg_job;

/*			BACKGROUND JOB NODES				*/
typedef struct s_bg_jobs
{
	pid_t				gpid;
	pid_t				*pid;
	char				***cmd;
	int					status;
	int					index;
	struct s_bg_jobs	*prev;
	struct s_bg_jobs	*next;
}						t_bg_jobs;

/*				PIPE DATA				*/
typedef struct s_pipe
{
	int		pid; //Is this even used?
	int		piping;
	int		new_pipe;
	int		write_pipe[2];
	int		read_pipe[2];
	int		redir_out;
	int		redir_in;
	int		stdincpy;
	int		stdoutcpy;
	int		fd_aliases[SH_FD_MAX + 1];
}			t_pipe;

/*				SESSION STRUCT				*/
typedef struct s_shell
{
	pid_t			pgid;
	t_term			term[1];
	int				process_queue[256];
	struct termios	orig_termios;
	t_hash			**ht;
	t_treenode		*head;
	t_token			*tokens;
	t_pipe			*pipe;
	t_fg_job		fg_node[1];
	t_bg_jobs		*bg_node;
	char			**intr_vars;
	char			**env;
	char			**tmp_env_key;
	char			**alias;
	char			**dup_alias;
	char			*line;
	char			*terminal;
	int				alias_size;
	int				process_count;
	int				exit_stat;
	int				is_flag_on;
	int				option_count;
	char			option;
	bool			ampersand;
	int				exit_confirm;
	int				sym_link;
}				t_shell;

	/*	libft 	*/
int				ft_iswhitespace(char c);
int				ft_strcount(char *str, char target);
void			ft_free_doublearray(char ***array);
char			**ft_create_empty_str_array(int size);
void			ft_copy_doublearray(char **src, char **dst);
char			**ft_dup_doublearray(char **original);
int				ft_strarray_size(char **arr);
void			ft_exit_error(char *msg, int ret);
char			*ft_strjoin_three(char *s1, char *s2, char *s3);
size_t			ft_strlen_match(char *str, char delimiter);			// ?
/*					ALIAS					*/
//	alias_add_quotes.c		(4)
void	add_quotes(char **content);
//	alias_array_handling.c	(2)
void	dup_arr_rm_pos(char **alias, char ***dup_alias, int pos, int size);
void	free_and_refill_dup_alias(char ***dup_alias, char **original);
//	alias_string_handling.c	(5)
void	append_to_converted(char **line, char **next, char **post);
void	trim_mid_word(char **mid, char **orig_post);
char	*get_mid_word(char *line);
//	alias_string_handling2.c 	(5)
int		skip_to_second_word(char *line);
void	remove_quotes_cmd(char *cmd);
void	get_first_word_move_post(char **post, char **next, char **line);
//	alias_utilities.c	(3)
int		word_count(char *line);
size_t	strip_quotes_single(char *str, size_t quote1);
//	alias.c	(4)
int		alias(t_shell *sh, char **args);
//	init_alias.c	(5)
void	init_alias(t_shell *sh);
//	match_alias.c	(2)
int		check_alias_match(char **aliases, char *cmd);
int		match_first_word(char **alias, char *line);
//	print_alias.c	(4)
int		print_alias_single(char *cmd, char **aliases);
void	print_alias_all(char **alias, t_shell *sh);
//	unalias.c	(5)
void	remove_alias_single(char ***alias, int rm_pos, int size);
int		unalias(t_shell *sh, char **args);
//	validate_alias.c	(4)
int		validate_alias(char *alias, int print_error);
int		validate_whitespace(char *str);


//	conversions

//	convert_alias.c
//	convert_alias2.c
//	get_alias.c
char	*get_post_content(char *line, char *arg);
char	*get_alias_content_no_quotes(char *alias);
char	*get_alias_command(char *alias);
char	*get_alias_content(char *alias);
int		is_command_separator(char command);
char	*get_first_word(char *line);

//	-	-	-	-	-	-

//	get_alias.c
// char			*get_post_content(char *line, char *arg);		// MALLOC
// char			*get_alias_content_no_quotes(char *alias);		// MALLOC
// char			*get_alias_command(char *alias);				// MALLOC
// char			*get_alias_content(char *alias);				// MALLOC
// char			*get_first_word(char *line);					// MALLOC

//	convert_alias.c
int				check_command_separator(char *line);
void			convert_first_word(char ***alias, char **line, int size);
char			*check_valid_input(char *line, int i);
// int				convert_alias(char **line, t_shell *sh, int pos);
void			alias_convert_line(char **line, t_shell *sh);
//	convert_alias2.c
int				check_next_conversion(char *alias);
void			update_alias_line(char **line, char **pre_semicolon);
// char			*convert_first(t_shell *sh, char ***dup_alias,
// char **line, char *cont);
// void			conversion_loop(t_shell *sh, char **line, char **content);
// void			conversion_dispatch(t_shell *sh, char **line,
// char **cont, int pos);

size_t  total_line_len(char *pre, char *convert, char *post, char **new_line);
void    free_parsed_alias_line(char **pre, char **conv, char **post, \
char **new_line);
void    connect_alias_pieces(char **pre, char **convert, char **post, \
char **line);
char	*convert_first(char ***dup, char ***alias, char **line, char *cont);
void	conversion_loop(char ***alias, char **line, char **content);
void	conversion_dispatch(char ***alias, char **line, char **content, int pos);
int	convert_alias(char ***dup_alias, char **line, int i);
void	check_line_separators(char ***alias, char **line);
int				is_command_separator(char command);
int	validate_char_range(char *str, int i, int start);	// no need ?
int	validate_reserved_keywords(char *str);			// no need ?
void	convert_dollar_tilde(char *cmd, int i, t_shell *sh);	// no need ?

/*					BUILDTREE				*/
t_treenode		*build_tree(t_token **tokens);
char			**make_arg_array(char *cmd);
int				foreseer_of_tokens(t_token *tokens, \
int mark, int start, int end);
t_treenode		*create_pipe_node(t_token *tokens, int i_tok, int end);
t_treenode		*create_semicolon_node(t_token *tokens, int i_tok, int end);
t_treenode		*parse_left_cmd(t_token *tokens, int i_tok);
t_treenode		*parse_right_cmd(t_token *tokens, int i_tok);
t_treenode		*parse_redirections(t_token *tokens, int i_tok, int cmd);
t_treenode		*init_cmd_node(char *cmd);
t_treenode		*init_redir_wrap(char *filepath, t_treenode *cmd, \
int redir_type, int close_fd);
int				calculate_tokens(t_token *tokens);
int				choose_redir_type(t_token *tokens, t_treenode **redir, \
int i_tok, int cmd);
int				if_closefd(t_token *tokens, t_treenode **redir, \
int i_tok, int cmd);
int				if_aggregation(t_token *tokens, t_treenode **redir, \
int i_tok, int cmd);
int				if_redir(t_token *tokens, t_treenode **redir, \
int i_tok, int cmd);
int				get_close_fd(char *value);
void			traverse_node(t_treenode **head);
char			*get_file(char *value);
int				error_tok(t_treenode *redir_head, char *msg, char *symbol);
void			combine_words(t_token *tokens);
int				test_if_file(char *file);
t_treenode		*create_command_tree(t_token *tokens, int i_tok, int semicol);
void			print_tree(t_treenode *head);
void			print_spaces(int lvl);
int				is_semicolon_or_ampersand(int token);
int				is_logicalop(int token);
t_treenode		*create_logical_op_tree(t_token *tokens, \
int i_tok, int semicol);
void			rec_print_tree(t_treenode *root, int lvl);
void			exec_logicalop(t_logicalop *logicalop, char ***environ_cp, \
char *terminal, t_shell *sh);
//t_treenode		*create_ampersand_node(t_token *tokens, int i_tok, int end);
t_treenode		*init_ampersand_node(void);
t_treenode		*init_semicolon(void);
void			print_exec(t_treenode *node);
void			check_type(t_treenode *root);
int				next_semicolon_or_ampersand(t_token *tokens, \
int i_tok, int end);

/*				BUILTIN UTILITIES			*/
int				ft_cd_addr_check(char *file, int p_option, t_shell *session);
t_bg_jobs		*search_via_cmd(t_shell *sh, char *arg, char *cmd);
t_bg_jobs		*bg_fetch_node(t_shell *sh, char *args, char *cmd);
int				ft_env_temp(t_shell *sh, char **cmd, int i);
void			ft_env_remove(t_shell *sh, char *env_to_clean);
int				ft_env_append(t_shell *sh, char **arg);
int				ft_env_replace(t_shell *sh, char *envn, char **tmp_env);
void			ft_dir_change(t_shell *sh);
int				check_flag(t_shell *session, char **commands, char flag);
int				print_usage(char *command, char c);
int				validate_cd_options(t_shell *session, char **commands, \
				int i, int dash_dash);
char			*trim_dots_helper(char **sub_dirs, char *trimmed, int i, \
				int to_skip);
int				cd_multi_command_validation(t_shell *sesh, char **commands);
int				str_only_contains_chars(char *str, char *options, t_shell *sh);
char			*trim_dots(char *file, int i);
void			trim_dot_dot_slash(char *path);
void			manipulate_env(t_shell *session, char *file);
void			add_var_env_quotes(char **cmd);
void			delete_var(t_shell *sh, int *i);
int				check_export_print(t_shell *sh, char **cmd);

/*					BUILTIN					*/
int				ft_builtins(t_shell *sesh, char ***cmd, char ***environ_cp);
int				ft_bg(t_shell *sh, char **cmd);
int				ft_cd(t_shell *sh, char **cmd);
int				ft_echo(t_shell *sh, char **cmd);
int				ft_set(t_shell *sh, char ***cmd);
int				ft_exit(t_shell *sesh, char **commands);
int				ft_fg(t_shell *sh, char **cmd);
int				ft_export(t_shell *sh, char **cmd);
int				ft_jobs(t_shell *sh, char **cmd);
int				ft_unset(t_shell *sh, char **cmd);
int				type_command(t_shell *sesh, char **commands, char **env, int i);

/*					EXEC_TREE			*/
int				check_access(char *cmd, char **args, t_shell *sh);
void			exec_tree(t_treenode *head, char ***environ_cp, \
char *terminal, t_shell *sh);
void			exec_cmd(t_cmdnode *head, char ***environ_cp, t_shell *sh);
void			exec_pipe(t_pipenode *pipenode, char ***environ_cp, \
char *terminal, t_shell *sh);
void			exec_ampersand(t_ampersand *head, char ***environ_cp, \
char *terminal, t_shell *sh);
void			exec_redir(t_redir *node, char ***environ_cp, \
char *terminal, t_shell *sh);
void			exec_aggregate(t_aggregate *node, char ***environ_cp, \
char *terminal, t_shell *sh);
void			exec_semicolon(t_semicolon *head, char ***environ_cp, \
char *terminal, t_shell *sh);
void			exec_closefd(t_closefd *node, char ***environ_cp, \
char *terminal, t_shell *sh);
char			*search_bin(char *cmd, char **environ_cp);
void			error_exit(char *msg);
size_t			calc_chptr(char **arr);
int				fork_wrap(void);
void			open_fd_if_needed(int *fd, char *terminal, t_shell *sh);
void			exe_fail(char **cmd, char **args, char ***env_cp);

/*					EXECUTE_UTILS			*/
int				check_access(char *cmd, char **args, t_shell *sh);
int				check_if_user_exe(char *cmd, char **dest);
void			exe_fail(char **cmd, char **args, char ***env_cp);

/*					EXPANSION				*/
void			ft_catinate_expansion(t_shell *sh, char **splits, \
char **buff, char qoute);
void			ft_expansion(t_shell *sh, char **cmd);
char			*ft_expansion_dollar(t_shell *sh, char *str);
char			*ft_expansion_tilde(t_shell *sh, char *str);
char			*ft_expansion_excla(char *str, int i);
void			ft_quote_blash_removal(char *buff);
char			*user_expansions(char *input);

/*				FT_TEST				*/
int				ft_test_b(char **arg);
int				ft_test_c(char **arg);
int				ft_test_capital_l(char **arg);
int				ft_test_capital_s(char **arg);
int				ft_test_check_int(char **arg, int not);
int				ft_test_d(char **arg);
int				ft_test_e(char **arg);
int				ft_test_eq(char **arg);
int				ft_test_equal(char **arg);
int				ft_test_f(char **arg);
int				ft_test_g(char **arg);
int				ft_test_ge(char **arg);
int				ft_test_gt(char **arg);
char			*ft_test_get_file_path(char **arg, int not);
int				ft_test_is_binary(char *str);
int				ft_test_is_not(char **arg);
int				ft_test_is_unary(char *str);
int				ft_test_le(char **arg);
int				ft_test_lt(char **arg);
int				ft_test_ne(char **arg);
int				ft_test_no_flags(char **str);
int				ft_test_not_equal(char **arg);
int				ft_test_not_return_last(int not);
int				ft_test_p(char **arg);
int				ft_test_r(char **arg);
int				ft_test_s(char **arg);
int				ft_test_u(char **arg);
int				ft_test_w(char **arg);
int				ft_test_x(char **arg);
int				ft_test_z(char **arg);
int				ft_test(t_shell *sh, char **cmd);

/*			  		 HASH					*/
int				ft_hash(t_shell *sh, char **cmd);
char			*hash_check(t_shell *sh, char *program, int *hash);
void			hash_clear(t_hash **ht);
void			hash_free(t_hash **ht);
size_t			hash_function(char *program);
void			hash_init_struct(t_shell *sh, char *str, int hits);
void			hash_init(t_shell *sh);
void			hash_print(t_hash **ht);

/*			  		 HISTORY				*/
int				ft_history(t_term *t, char **cmd);
void			ft_history_get(t_term *t);
int				ft_history_print_error(char *str, int prefix);
int				ft_history_expantion(t_term *t);
void			ft_history_write_to_file(t_term *t);

/*				  INITIALIZE				*/
void			ft_init_signals(void);
void			ft_init_fg_node(t_shell *sh);
void			init_window_size(t_term *term);
void			ft_env_init(t_shell *sh);
void			ft_session_init(t_shell *sh);

/*			  		 FC						*/
void			fc_build_and_execute_new_tree(t_shell *sh, t_fc *fc);
int				fc_error_check_for_no_flag_or_e_flag(t_shell *sh, \
t_fc *fc, char ***cmd);
void			fc_free(t_fc *fc);
int				fc_get_flags(t_fc *fc, char **cmd);
void			fc_get_start_and_end(t_shell *sh, t_fc *fc, char ***cmd);
int				fc_list_flags(t_shell *sh, t_fc *fc, char ***cmd);
int				fc_no_flag_or_e_flag(t_shell *sh, t_fc *fc, char ***cmd);
int				fc_no_flags(t_fc *fc);
void			fc_open_editor(char *editor, t_shell *sh, \
t_fc *fc, char ***cmd);
void			fc_overwrite_fc_cmd_with_prev_cmd(t_shell *sh, \
char ***cmd, int y);
int				fc_print_error(int check);
int				fc_s_change(t_shell *sh, char ***cmd);
int				fc_s_flag(t_shell *sh, t_fc *fc, char ***cmd);
void			fc_update_history(t_shell *sh, char ***cmd);
int				fc_usage(char *str);
int				ft_fc(t_shell *sh, char ***cmd);

/*			  	INTERN VARIABLES			*/
int				ft_variables(t_shell *sh, char ****cmd);
int				add_var(t_shell *sh, char **cmd);
int				is_var(char *cmd);
int				find_var(t_shell *sh, char *cmd, int var_len, int *ret);
char			**ft_var_get(t_shell *sh, char *key, int *count);
void			add_var_quotes(t_shell *sh, int i);


/*					JOBS					*/
void			append_cmd_arr(t_fg_job *fg_node, char **cmd);
void			append_pid_arr(t_fg_job *fg_node, pid_t pid);
void			bg_node_delete(t_shell *sh, t_bg_jobs **curr);
void			delete_from_queue(t_shell *sh, t_bg_jobs *process);
void			display_job_node(t_shell *sh, t_bg_jobs *job);
void			display_job_pipeline(t_shell *sh, t_bg_jobs *job);
void			display_bg_job(t_shell *sh);
void			display_suspended_job(t_shell *sh, int pid);
void			display_pipeline_cmd(t_shell *sh, t_bg_jobs *job);
char			**dup_dbl_ptr(char **cmd);
void			reset_fgnode(t_shell *sh);
void			set_process_group(t_shell *sh, pid_t pid);
void			add_to_queue(t_shell *sh, int index);
void			init_cmd(t_shell *sh, t_bg_jobs *bg_node);
void			init_pid(t_shell *sh, t_bg_jobs *bg_node);
void			transfer_to_bg(t_shell *sh, int status);
void			transfer_to_fg(t_shell *sh, t_bg_jobs *bg_node);
size_t			triple_ptr_len(char ***arr);
void			update_fg_job(t_shell *sh, pid_t pid, char **cmd);
void			wait_for_job(t_shell *sh, int pid);
void			reap_process(t_shell *sh);
void			update_job_status(t_shell *sh, int status, int pid);

/*		KEYYBOARD HAS IT'S OWN H-FILE		*/

/*					LEXER					*/
char			*ft_lexer(t_term *t);
char			*ft_heredoc(t_term *t, char *str);

/*				   MAIN 					*/
void			shell_end_cycle(t_shell *sh);
void			reset_fd(t_shell *sh);

/*				PARAM_FORM					*/
void			add_var_to_list(t_shell *sh, char *var, char *subst);
char			*retokenize(char *subst, int *i);
char			*substitute_or_create(t_shell *sh, char *cmd, int *ret);
char			*search_from_var(t_shell *sh, char *cmd, int *ret);
int				param_format(char **cmd);
void			substitute_og_cmd(t_param *pa, char **cmd, int *j);
char			*remove_braces(char *str);
char			*get_value(t_shell *sh, char *var, char *subst, int format);
int				format_mode(char op);
int				join_values(t_shell *sh, t_param *pa, char *cmd, int ret);
char			*get_operator(char *cmd);
int				is_param_exp_char(char *flag);
int				splitter(char *cmd, t_param *pa, int *ret);
int				expander(t_param *pa, int ret);
void			variable_length(char *str, t_param *pa);
int				perform_param_expans(char *cmd, t_param *pa, int *ret);
char			*get_flag(char *cmd, int *ret);
void			init_pa(t_param *pa);
void			init_pa_ints(t_pa_ints *ints);
void			free_attrs(t_param *pa, char **new_cmd);
void			init_subs_session(t_sub *sub, char *cmd);
void			subs_session_free(t_sub *sub, int opt);
char			*ft_find_word(char *haystack, char *needle, char *op);
void			remove_globstars(char **needle, int *glob);
char			*find_from_end(char *haystack, char *needle);
char			*find_from_begin_glob(char *haystack, char *needle);
int				is_substring_id(char *needle);
int				check_var_validity(char *var);
int				check_substitutions(char *cmd, int *ret, t_param *pa);
void 			temp_free(char ***temp);

/*			  		 SIGNALS				*/
void			ft_signal_keyboard(int num);
void			search_history_sigs(int num);
void			ft_signal_dfl(void);
void			set_signal_keyboard(void);
void			set_signal_search_history(void);

/*					TERMIOS				*/
int				ft_getent(void);
void			ft_raw_enable(t_shell *sh);
void			ft_raw_disable(struct termios orig_termios);

/*					TOKENIZER				*/
t_token			*chop_line(char *line, t_token *args, size_t pointer_n);
char			*find_argument(char *line, int *i, int *start, int *end);
void			init_token(char *c, t_token *token, char *line, int cur);
void			track_used_space(t_token **args, size_t current_pointer_n, \
size_t *max_pointer_n);
int				test_if_error(char *str);
char			*tok_if_redir(char *line, int *i, int *start, int *end);
int				redir_error(char *str);
int				test_if_error(char *str);
char			*tok_if_logical(char *line, int *i, int *start, int *end);
void			print_tokens(t_token *tokens);
int				validate_tokens(t_token *tokens);

/*					TOKENIZER UTILS			*/
int				is_semi_or_amp(char c);
void			free_tokens(t_token **tokens);
int				is_seperator(char c);
void			tok_quote_flag(char *line, int *end, t_token_flags *flags);

/*					UTILITIES				*/
void			banner_print(void);
void			exit_error(t_shell *sh, int status, char *msg);
char			**ft_env_get(t_shell *sh, char *key, char **from_array);
int				increment_whitespace(char **line);
void			free_node(t_treenode *head);
int				ft_err_print(char *file, char *cmd, char *msg, int fd);
int				ft_isseparator(char c);
void			ft_env_last_command(t_shell *sh, char **cmd);
void			ft_print_dbl_array(char **cmd);
int				ft_prog_error_int_print(char *arg, char *prog);
int				int_check_validity(char *arg, char *prog);
void			reset_cmd(char ****cmd);
void			jobs_exit_check(t_shell *sh);
int				give_alias_for_fd(t_shell *sh, int *fd);
int				alias_fd_if_necessary(t_shell *sh, int *fd);
int				close_fd_alias_if_necessary(t_shell *sh, int fd);
int				is_aliased_fd(t_shell *sh, int open_fd);
void			print_aliases(t_shell *sh);
int				is_alias_fd(t_shell *sh, int fd);
int				close_fd_alias(t_shell *sh, int fd);
void			init_flags_struct(t_token_flags *flags);

#endif
