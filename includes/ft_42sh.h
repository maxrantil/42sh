/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_42sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:32:09 by mrantil           #+#    #+#             */
/*   Updated: 2023/02/25 20:40:41 by jniemine         ###   ########.fr       */
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

/* Jobs States */
# define SIG_HANGUP

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

/*			PARAMETER EXPANSION SUBSTRING QUOTES	*/
typedef struct s_subquo
{
	int		d_quote;
	int		s_quote;
	int		i;
	int		k;
	int		closed;
	char	*new;
}	t_subquo;

/*			PARAMETER EXPANSION PERCENT	*/
typedef struct s_perc
{
	int		len;
	int		temp_len;
	char	*new_needle;
	char	*temp;
}	t_perc;

/*			PARAMETER EXPANSION RETOKENIZE	*/
typedef struct s_retok
{
	int		k;
	int		open;
	char	*fresh;
}	t_retok;

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
	int		pid;
	int		piping;
	int		new_pipe;
	int		write_pipe[2];
	int		read_pipe[2];
	int		redir_out;
	int		redir_in;
	int		stdincpy;
	int		pipes[SH_FD_MAX][2];
	int		pipe_idx;
	int		fd_aliases[SH_FD_MAX + 1];
	int		open_fd_idx;
	int		closed_fds[SH_FD_MAX];
	int		previous_redir[SH_FD_MAX];
	int		read_fd;
	int		write_fd;
	int		close_fd;
	int		redir_fork;
	int		interrupt;
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
	int				exit_confirm;
	int				sym_link;
	int				arr_len;
	char			option;
	bool			ampersand;
	int				temp_env_bool;
	char			**temp_env;
}				t_shell;

/*					ALIAS					*/
int				ft_iswhitespace(char c);
int				ft_strcount(char *str, char target);
void			ft_free_doublearray(char ***array);
char			**ft_create_empty_str_array(int size);
void			ft_copy_doublearray(char **src, char **dst);
char			**ft_dup_doublearray(char **original);
int				ft_strarray_size(char **arr);
void			ft_exit_error(char *msg, int ret);
char			*ft_strjoin_three(char *s1, char *s2, char *s3);
size_t			ft_strlen_match(char *str, char delimiter);
void			alias_heredoc_check(char **line);
void			dup_arr_rm_pos(char **alias, char ***dup, int pos, int size);
void			free_and_refill_dup_alias(char ***dup_alias, char **original);
int				validate_alias(char *alias, int print_error);
int				validate_whitespace(char *str);
void			add_quotes(char **content);
void			append_to_converted(char **line, char **next, char **post);
void			trim_mid_word(char **mid, char **orig_post);
char			*get_mid_word(char *line, char **next);
int				skip_to_second_word(char *line);
void			remove_quotes_cmd(char *cmd);
void			get_first_word_move_post(char **post, char **next, char **line);
int				word_count(char *line);
size_t			strip_quotes_single(char *str, size_t quote1);
int				alias(t_shell *sh, char **args);
void			init_alias(t_shell *sh);
int				check_alias_match(char **aliases, char *cmd);
int				match_first_word(char **alias, char *line);
int				print_alias_single(char *cmd, char **aliases);
void			print_alias_all(char **alias, t_shell *sh);
void			remove_alias_single(char ***alias, int rm_pos, int size);
int				unalias(t_shell *sh, char **args);
void			alias_convert_line(char **line, t_shell *sh);
int				is_command_separator(char command);
void			check_line_separators(char ***alias, char **line);
void			connect_alias_pieces(char **pr, char **c, char **pos, char **l);
void			convert_first_word(char ***alias, char **line, int size);
void			trim_alias_line(char **line);
void			conversion_dispatch(char ***ali, char **li, char **con, int p);
int				convert_alias(char ***dup_alias, char **line, int i);
int				check_next_conversion(char **alias, int del);
char			*convert_first(char ***dup, char ***ali, char **lin, char *con);
void			conversion_loop(char ***ali, char **li, char **con, char ***du);
char			*get_post_content(char *line, char *arg);
char			*get_alias_content_no_quotes(char *alias);
char			*get_alias_command(char *alias);
char			*get_alias_content(char *alias);
char			*get_first_word(char *line);

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
t_treenode		*init_ampersand_node(void);
t_treenode		*init_semicolon(void);
void			print_exec(t_treenode *node);
void			check_type(t_treenode *root);
t_treenode		*init_logical_op(int type);
int				is_pipe(t_shell *sh, int fd);

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
int				is_path_symlink(char *path);
int				cd_minus_symlink(t_shell *sh, char *path);
void			erase_last_subdir(char *path);
int				resolve_dotdot_symlink(t_shell *sh, char **cmd);
int				cd_symlink_utils_free(char **path, int ret);
void			reset_options(t_shell *sh);
char			*env_path(t_shell *sh, char *key);
int				ft_chdir_expanded(t_shell *sh, char **path);
void			add_var_env_quotes(char **cmd);
void			delete_var(t_shell *sh, int *i);
int				check_export_print(t_shell *sh, char **cmd);
char			*lower_case(char *cmd);

/*					BUILTIN					*/
int				fork_if_pipe(t_shell *sh, char ***cmd, char ***environ_cp);
int				ft_builtins(t_shell *sesh, char ***cmd, char ***environ_cp);
int				ft_bg(t_shell *sh, char **cmd);
int				ft_cd(t_shell *sh, char **cmd);
int				ft_echo(t_shell *sh, char **cmd);
int				ft_set(t_shell *sh, char ***cmd);
int				ft_exit(t_shell *sesh, char **commands);
int				ft_fg(t_shell *sh, char **cmd);
int				ft_export(t_shell *sh, char **cmd, int opt);
int				ft_jobs(t_shell *sh, char **cmd);
int				ft_unset(t_shell *sh, char **cmd);
int				cmd_comparisons(t_shell *sh, char ***cmd, char ***environ_cp);
int				type_command(t_shell *sesh, char **commands, char **env, int i);
int				is_builtin(char **cmd);

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
int				test_access_type(char *dest, int closefd, int *rights, \
t_shell *sh);
int				is_nb(char *str);
int				test_file_access(char *file);
void			redir_to_file(t_aggregate *node, t_shell *sh);
char			**get_cmd_name(t_treenode *node);

/*					EXECUTE_UTILS			*/
int				check_access(char *cmd, char **args, t_shell *sh);
int				check_if_user_exe(char *cmd, char **dest);
void			exe_fail(char **cmd, char **args, char ***env_cp);
void			exec_aggre_errors(t_aggregate *node, t_shell *sh, \
int builtin);

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
void			ft_history_print_add_row(t_term *t);
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
int				fc_s_change(t_shell *sh, t_fc *fc, char ***cmd, int y);
int				fc_s_flag(t_shell *sh, t_fc *fc, char ***cmd);
void			fc_update_history(t_shell *sh, char ***cmd);
int				fc_usage(char option, char *str);
int				ft_fc(t_shell *sh, char ***cmd);
int				get_history_cap(t_shell *sh);

/*			  	INTERN VARIABLES			*/
int				ft_variables(t_shell *sh, char ***cmd);
int				add_var(t_shell *sh, char **cmd);
int				is_var(char *cmd);
int				find_var(t_shell *sh, char *cmd, int var_len, int *ret);
char			**ft_var_get(t_shell *sh, char *key, int *count);
void			add_var_quotes(t_shell *sh, int i);
void			free_temp_env(t_shell *sh);

/*					JOBS					*/
void			append_cmd_arr(t_fg_job *fg_node, char **cmd);
void			append_pid_arr(t_fg_job *fg_node, pid_t pid);
void			bg_node_delete(t_shell *sh, t_bg_jobs **curr);
void			change_process_status(t_bg_jobs *bg_node, pid_t pid, \
				int status);
void			display_job_node(t_shell *sh, t_bg_jobs *job);
void			display_job_pipeline(t_shell *sh, t_bg_jobs *job);
void			display_bg_job(t_shell *sh);
void			display_suspended_job(t_shell *sh, int pid);
void			display_pipeline_cmd(t_shell *sh, t_bg_jobs *job);
char			**dup_dbl_ptr(char **cmd);
void			queue_remove(t_shell *sh, t_bg_jobs *process);
void			queue_move_to_front(t_shell *sh, t_bg_jobs *process);
void			reset_fgnode(t_shell *sh);
void			set_process_group(t_shell *sh, pid_t pid);
void			init_cmd(t_shell *sh, t_bg_jobs *bg_node);
void			init_pid(t_shell *sh, t_bg_jobs *bg_node);
void			transfer_to_bg(t_shell *sh, int status);
void			transfer_to_fg(t_shell *sh, t_bg_jobs *bg_node);
size_t			triple_ptr_len(char ***arr);
void			update_fg_job(t_shell *sh, pid_t pid, char **cmd);
void			wait_for_job(t_shell *sh, int pid);
void			reap_process(t_shell *sh);
void			update_job_status(t_shell *sh, int status, int pid, int mode);
void			job_wtermsig_msg(int status);

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
char			*get_value(t_shell *sh, char *var, char *subst, int *format);
int				format_mode(char op);
int				join_values(t_shell *sh, t_param *pa, char *cmd, int *ret);
char			*get_operator(char *cmd);
int				is_param_exp_char(char *flag);
int				splitter(char *cmd, t_param *pa, int *ret);
void			variable_length(char *str, t_param *pa);
int				perform_param_expans(char *cmd, t_param *pa, int *ret);
char			*get_flag(char *cmd, int *ret);
void			init_pa(t_param *pa);
void			init_pa_ints(t_pa_ints *ints);
void			free_attrs(t_param *pa, char **new_cmd);
void			init_subs_session(t_sub *sub, char *cmd);
void			subs_session_free(t_sub *sub, int opt);
char			*ft_find_word(char *haystack, char *needle, char *op);
char			*remove_globstars(char **needle, int *glob, char op);
char			*find_from_end(char *haystack, char *needle, int glob);
char			*find_from_begin_glob(char *haystack, char *needle);
int				is_substring_id(char *needle);
int				check_var_validity(char *var);
int				check_substitutions(char *cmd, int *ret, t_param *pa);
void			temp_free(char ***temp);
void			trim_and_remove_null(char ***cmd, t_pa_ints *ints);
char			*get_word(char *temp, char *temp_needle, char *op, int glob);
char			*remove_quotes_subs(char **str);
int				check_param_format_seq(t_param *pa);

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
int				is_std_fd_cpy(t_shell *sh, int fd);
void			init_flags_struct(t_token_flags *flags);

#endif
