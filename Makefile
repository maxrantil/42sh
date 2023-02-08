# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/12 06:01:22 by mbarutel          #+#    #+#              #
#    Updated: 2023/02/08 09:26:48 by mviinika         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#COLORS
SHELL 				:= /bin/bash
GREEN 				= \033[32m
GREEN_BACKGROUND 	= \033[42m
WHITE_BACKGROUND	= \033[47m
VIOLET_BACKGROUND	= \033[0;45m
YELLOW_BACKGROUND	= \033[0;43m
CYAN_BACKGROUND		= \033[46m
WHITE				= \033[37m
YELLOW				= \033[33m
BLACK				= \033[30m
VIOLET				= \033[35m
RESET				= \033[0m
RED					= \033[31m
CYAN				= \033[36m
BOLD				= \033[1m

#PRINTING TOOLS
ERASE_LINE 			= \033[K
UP 					= A
DOWN 				= B
RIGHT 				= C
LEFT				= D
MOVE 				= \033[
C_INVISIBLE			= \033[?25l
C_VISIBLE			= \033[?25h

MAKEFLAGS			+= --no-print-directory

NAME				=	42sh
CC					=	gcc
TERMCAP				=	-ltermcap
CFLAGS 				= 	-Wall -Wextra
CFLAGS				+=	-Wunreachable-code -Wtype-limits
CFLAGS				+=	-Wpedantic
# CFLAGS				+=	-Wconversion
CFLAGS				+=	-O3

LEAK_CHECK			= -g
LEAK_CHECK			+=	-fsanitize=address

UNAME				= $(shell uname)
ifeq ($(UNAME), Darwin)
#CFLAGS				+= 	-Werror
endif
ifeq ($(UNAME), Linux)
TERMCAP				=	-lncurses
endif

SOURCES 		= 	sources
INCLUDES		= 	includes/
LIBRARIES 		= 	libft/
BANNER			= 	banner/
BUILDTREE		=	build_tree/
BUILTIN_UTILS	= 	builtin_utils/
BUILTIN			= 	builtins/
EXECTREE		=	exec_tree/
EXPANSION		=	expansion/
FC				= 	fc/
FT_TEST			=	ft_test/
HASH			= 	hash/
HISTORY			= 	history/
INITIALIZE		=	initialize/
INTERN_VARS		=	intern_variables/
JOBS			= 	jobs/
KEYBOARD		= 	keyboard/
LEXER			= 	lexer/
MAIN			= 	main/
PARAM_FORM		=	parameter_formatting/
SIGNALS			= 	signals/
TERMIOS			= 	termios/
TOKENIZER		=	tokenizer/
UTILITIES		=	utilities/
OBJECTS 		= 	objects

SOURCE_COUNT = $(words $(FILES))

H_FILES 	= 	ft_42sh \
				keyboard \

FILES			= \
				$(BANNER)ft_banner \
				$(BUILDTREE)build_tree \
				$(BUILDTREE)make_arg_array \
				$(BUILDTREE)bt_utils \
				$(BUILDTREE)bt_utils_2 \
				$(BUILDTREE)bt_utils_more \
				$(BUILDTREE)bt_create_pipe_node \
				$(BUILDTREE)bt_create_semicolon_node \
				$(BUILDTREE)bt_parse_redirections \
				$(BUILDTREE)bt_choose_redir_type \
				$(BUILDTREE)bt_if_closefd \
				$(BUILDTREE)bt_if_redir \
				$(BUILDTREE)bt_if_aggregation \
				$(BUILDTREE)bt_error_tok \
				$(BUILDTREE)bt_get_file \
				$(BUILDTREE)bt_combine_words \
				$(BUILDTREE)bt_print_tree \
				$(BUILDTREE)bt_create_logicalop_tree \
				$(BUILDTREE)bt_create_command_tree \
				$(BUILDTREE)bt_create_ampersand_node \
				$(BUILDTREE)bt_print_exec \
				$(BUILDTREE)bt_check_type \
				$(BUILTIN_UTILS)ft_cd_addr_check \
				$(BUILTIN_UTILS)ft_dir_change \
				$(BUILTIN_UTILS)ft_env_append \
				$(BUILTIN_UTILS)ft_env_remove \
				$(BUILTIN_UTILS)ft_env_replace \
				$(BUILTIN_UTILS)ft_env_temp \
				$(BUILTIN)ft_builtins \
				$(BUILTIN)ft_cd \
				$(BUILTIN)ft_echo \
				$(BUILTIN)ft_set \
				$(BUILTIN)ft_exit \
				$(BUILTIN)ft_export \
				$(BUILTIN)ft_unset \
				$(EXECTREE)check_access \
				$(EXECTREE)check_if_user_exe \
				$(EXECTREE)exe_fail \
				$(EXECTREE)exec_tree \
				$(EXECTREE)exec_cmd \
				$(EXECTREE)exec_pipe \
				$(EXECTREE)exec_redir \
				$(EXECTREE)exec_closefd \
				$(EXECTREE)exec_aggregation \
				$(EXECTREE)search_bin \
				$(EXECTREE)exe_open_fd_if_needed \
				$(EXECTREE)exe_test_if_file \
				$(EXECTREE)exe_logicalop \
				$(EXPANSION)ft_catinate_expansion \
				$(EXPANSION)ft_expansion \
				$(EXPANSION)ft_expansion_utils \
				$(EXPANSION)ft_expansion_dollar \
				$(EXPANSION)ft_expansion_tilde \
				$(EXPANSION)ft_expansion_excla \
				$(FC)fc_build_and_execute_new_tree \
				$(FC)fc_check_flags \
				$(FC)fc_error_check_for_no_flag_or_e_flag \
				$(FC)fc_get_start_and_end \
				$(FC)fc_get_start_for_lists \
				$(FC)fc_list_flags \
				$(FC)fc_no_flag_or_e_flag \
				$(FC)fc_open_editor \
				$(FC)fc_overwrite_fc_cmd_with_prev_cmd \
				$(FC)fc_print_error \
				$(FC)fc_s_change \
				$(FC)fc_s_flag \
				$(FC)fc_update_history \
				$(FC)ft_fc \
				$(FT_TEST)ft_test_b \
				$(FT_TEST)ft_test_c \
				$(FT_TEST)ft_test_capital_l \
				$(FT_TEST)ft_test_capital_s \
				$(FT_TEST)ft_test_check_int \
				$(FT_TEST)ft_test_d \
				$(FT_TEST)ft_test_e \
				$(FT_TEST)ft_test_eq \
				$(FT_TEST)ft_test_equal \
				$(FT_TEST)ft_test_error_int_print \
				$(FT_TEST)ft_test_f \
				$(FT_TEST)ft_test_g \
				$(FT_TEST)ft_test_ge \
				$(FT_TEST)ft_test_gt \
				$(FT_TEST)ft_test_get_file_path \
				$(FT_TEST)ft_test_is_binary \
				$(FT_TEST)ft_test_is_unary \
				$(FT_TEST)ft_test_is_not \
				$(FT_TEST)ft_test_le \
				$(FT_TEST)ft_test_lt \
				$(FT_TEST)ft_test_ne \
				$(FT_TEST)ft_test_not_equal \
				$(FT_TEST)ft_test_not_return_last \
				$(FT_TEST)ft_test_p \
				$(FT_TEST)ft_test_r \
				$(FT_TEST)ft_test_s \
				$(FT_TEST)ft_test_u \
				$(FT_TEST)ft_test_w \
				$(FT_TEST)ft_test_x \
				$(FT_TEST)ft_test_z \
				$(FT_TEST)ft_test \
				$(HASH)ft_hash \
				$(HASH)hash_check \
				$(HASH)hash_clear \
				$(HASH)hash_free \
				$(HASH)hash_function \
				$(HASH)hash_init_struct \
				$(HASH)hash_init \
				$(HASH)hash_print \
				$(INITIALIZE)ft_env_init \
				$(INITIALIZE)ft_init_window_size \
				$(INITIALIZE)ft_session_init \
				$(INITIALIZE)ft_init_jobs \
				$(INTERN_VARS)ft_variables \
				$(INTERN_VARS)add_var \
				$(INTERN_VARS)ft_var_get \
				$(JOBS)jobs_attach_fg_grp \
				$(JOBS)jobs_detach_and_remove_fg_grp \
				$(JOBS)jobs_detach_fg_grp \
				$(JOBS)jobs_reset_fg_grp \
				$(HISTORY)ft_history \
				$(HISTORY)ft_history_get \
				$(HISTORY)ft_history_expansion \
				$(HISTORY)ft_history_write_to_file \
				$(KEYBOARD)ft_add_nl_last_row \
				$(KEYBOARD)ft_add_nl_mid_row \
				$(KEYBOARD)ft_alt_mv \
				$(KEYBOARD)ft_arrow_input \
				$(KEYBOARD)ft_backspace \
				$(KEYBOARD)ft_bracket_handling \
				$(KEYBOARD)ft_special_char_check \
				$(KEYBOARD)ft_copy \
				$(KEYBOARD)ft_create_prompt_line \
				$(KEYBOARD)ft_ctrl_d \
				$(KEYBOARD)ft_cut \
				$(KEYBOARD)ft_end_cycle \
				$(KEYBOARD)ft_get_input \
				$(KEYBOARD)ft_get_term_val \
				$(KEYBOARD)ft_heredoc_handling \
				$(KEYBOARD)ft_init \
				$(KEYBOARD)ft_line_down \
				$(KEYBOARD)ft_line_up \
				$(KEYBOARD)ft_paste \
				$(KEYBOARD)ft_putc \
				$(KEYBOARD)ft_quote_decrement \
				$(KEYBOARD)ft_quote_handling \
				$(KEYBOARD)ft_quote_flag_check \
				$(KEYBOARD)ft_quote_flag_reset \
				$(KEYBOARD)ft_setcursor \
				$(KEYBOARD)ft_shift_insert \
				$(KEYBOARD)ft_trigger_nl \
				$(KEYBOARD)ft_delete \
				$(KEYBOARD)ft_deletion_shift \
				$(KEYBOARD)ft_delim_fetch \
				$(KEYBOARD)ft_esc_parse \
				$(KEYBOARD)ft_get_prompt_len \
				$(KEYBOARD)ft_history_trigger \
				$(KEYBOARD)ft_input_cycle \
				$(KEYBOARD)ft_insertion \
				$(KEYBOARD)ft_mv_prompt_len \
				$(KEYBOARD)ft_is_prompt_line \
				$(KEYBOARD)ft_len_lowest_line \
				$(KEYBOARD)ft_line_mv \
				$(KEYBOARD)ft_print_trail \
				$(KEYBOARD)ft_remove_nl_addr \
				$(KEYBOARD)ft_reset_nl_addr \
				$(KEYBOARD)ft_restart_cycle \
				$(KEYBOARD)ft_row_lowest_line \
				$(KEYBOARD)ft_run_capability \
				$(KEYBOARD)ft_search_history_display \
				$(KEYBOARD)ft_search_history_edit \
				$(KEYBOARD)ft_search_history_init \
				$(KEYBOARD)ft_search_history_move \
				$(KEYBOARD)ft_search_history_reset \
				$(KEYBOARD)ft_search_history_utils \
				$(KEYBOARD)ft_search_history \
				$(KEYBOARD)ft_shift_nl_addr \
				$(KEYBOARD)ft_window_size \
				$(KEYBOARD)ft_word_mv \
				$(KEYBOARD)ft_ctrl \
				$(KEYBOARD)ft_history_reset_nl \
				$(KEYBOARD)ft_history_trigger_row \
				$(KEYBOARD)ft_nl_removal \
				$(KEYBOARD)ft_print_input \
				$(KEYBOARD)ft_history_add \
				$(KEYBOARD)ft_set_cur_position \
				$(KEYBOARD)ft_keyboard \
				$(LEXER)ft_lexer \
				$(LEXER)ft_heredoc \
				$(MAIN)main \
				$(MAIN)shell_end_cycle \
				$(MAIN)reset_fd \
				$(PARAM_FORM)add_var_to_list \
				$(PARAM_FORM)parameter_format \
				$(PARAM_FORM)retokenize \
				$(PARAM_FORM)substitute_or_create \
				$(PARAM_FORM)search_from_var \
				$(PARAM_FORM)free_param \
				$(PARAM_FORM)remove_braces \
				$(SIGNALS)handler_signal_exec \
				$(SIGNALS)handler_signal_keyboard \
				$(SIGNALS)handler_signal_search_history \
				$(SIGNALS)set_signal_dfl \
				$(SIGNALS)set_signal_exec \
				$(SIGNALS)set_signal_ign \
				$(SIGNALS)set_signal_keyboard \
				$(SIGNALS)set_signal_search_history \
				$(TERMIOS)ft_getent \
				$(TERMIOS)ft_raw_disable \
				$(TERMIOS)ft_raw_enable \
				$(TOKENIZER)tokenizer \
				$(TOKENIZER)token_utils \
				$(TOKENIZER)tok_find_argument \
				$(TOKENIZER)init_token \
				$(TOKENIZER)track_used_space \
				$(TOKENIZER)free_tokens \
				$(TOKENIZER)tok_if_logical \
				$(TOKENIZER)tok_if_redir \
				$(TOKENIZER)tok_error_after_tokenizing \
				$(TOKENIZER)tok_errors \
				$(TOKENIZER)tok_print_tokens \
				$(UTILITIES)ft_env_get \
				$(UTILITIES)ft_err_print \
				$(UTILITIES)free_node \
				$(UTILITIES)calc_chptr \
				$(UTILITIES)ft_isseparator \
				$(UTILITIES)ft_last_command_update \

H_PATHS 	= 	$(addsuffix .h, $(addprefix $(INCLUDES)/, $(H_FILES)))
O_PATHS		=	$(addsuffix .o, $(addprefix $(OBJECTS)/,$(FILES)))
LIBS		= 	libft/libft.a

HEADERS		=	-I$(INCLUDES)/ -Ilibft/includes/

ASSERT_OBJECT = && printf "$(ERASE_LINE)" && printf "$@ $(GREEN)$(BOLD) ✓$(RESET)" || (printf "$@ $(RED)$(BOLD)✘$(RESET)\n\n" | printf "$(C_VISIBLE)" && exit 1)

all: libft $(NAME)

$(NAME): libft/libft.a $(OBJECTS) $(O_PATHS)
	@$(CC) $(CFLAGS) $(HEADERS) -o $@ $(O_PATHS) $(LIBS) $(TERMCAP) $(LEAK_CHECK)
	@printf "Compiled $(BOLD)$(GREEN)$(NAME)$(RESET)!\n\n"
	@printf "$(C_VISIBLE)"

$(OBJECTS):
	@make -C $(LIBRARIES)
	@mkdir -p $(OBJECTS)/$(BANNER)
	@mkdir -p $(OBJECTS)/$(BUILDTREE)
	@mkdir -p $(OBJECTS)/$(BUILTIN_UTILS)
	@mkdir -p $(OBJECTS)/$(BUILTIN)
	@mkdir -p $(OBJECTS)/$(EXECTREE)
	@mkdir -p $(OBJECTS)/$(EXPANSION)
	@mkdir -p $(OBJECTS)/$(FC)
	@mkdir -p $(OBJECTS)/$(FT_TEST)
	@mkdir -p $(OBJECTS)/$(HASH)
	@mkdir -p $(OBJECTS)/$(HISTORY)
	@mkdir -p $(OBJECTS)/$(INITIALIZE)
	@mkdir -p $(OBJECTS)/$(INTERN_VARS)
	@mkdir -p $(OBJECTS)/$(JOBS)
	@mkdir -p $(OBJECTS)/$(KEYBOARD)
	@mkdir -p $(OBJECTS)/$(LEXER)
	@mkdir -p $(OBJECTS)/$(MAIN)
	@mkdir -p $(OBJECTS)/$(PARAM_FORM)
	@mkdir -p $(OBJECTS)/$(SIGNALS)
	@mkdir -p $(OBJECTS)/$(TERMIOS)
	@mkdir -p $(OBJECTS)/$(TOKENIZER)
	@mkdir -p $(OBJECTS)/$(UTILITIES)
	@printf "$(GREEN)_________________________________________________________________\n$(RESET)"
	@printf "$(NAME): $(GREEN)$(OBJECTS) directory was created.$(RESET)\n\n\n"

$(O_PATHS):	$(OBJECTS)/%.o:$(SOURCES)/%.c $(H_PATHS) Makefile
	@printf "$(C_INVISIBLE)"
	@printf "$(MOVE)2$(UP)"
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@ $(LEAK_CHECK) $(ASSERT_OBJECT)
	@make pbar

libft:
	@make -C $(LIBRARIES)
	@if [ "$(FOO)" = "" ]; then $(MAKE) FOO=bar; fi

clean:
	@make -C $(LIBRARIES) clean
	@if [ -d $(OBJECTS) ]; then rm -rf $(OBJECTS); printf "$(NAME):		$(RED)$(OBJECTS)/ was deleted$(RESET)\n"; fi

fclean: clean
	@make -C $(LIBRARIES) fclean
	@if [ -f $(LIBS) ]; then rm $(LIBS); fi
	@if [ -f $(NAME) ]; then rm -f $(NAME); printf "$(NAME):		$(RED)executable was deleted$(RESET)\n"; fi

re: fclean all

pbar:
	$(eval LOADED_COUNT = $(words $(shell find $(OBJECTS) -name '*.o')))
	@printf "\r$(MOVE)76$(RIGHT)Files compiled [$(BOLD)$(CYAN)$(LOADED_COUNT)$(RESET) / $(BOLD)$(CYAN)$(SOURCE_COUNT)$(RESET)]\n"
	@for ((i = 1; i <= $(LOADED_COUNT) * 100 / $(SOURCE_COUNT); i++)); do\
		printf "$(CYAN_BACKGROUND) $(RESET)" ;\
	done ;
	@for ((i = 1; i <= 100 - ($(LOADED_COUNT) * 100 / $(SOURCE_COUNT)); i++)); do\
		printf "$(WHITE_BACKGROUND) $(RESET)" ;\
	done ;
	@printf "$(CYAN_BACKGROUND)$(BOLD)$(WHITE)$(MOVE)55$(LEFT)[$$(($(LOADED_COUNT) * 100 / $(SOURCE_COUNT))).$$(($(LOADED_COUNT) * 1000 / $(SOURCE_COUNT) % 10))%%]$(MOVE)54$(RIGHT)$(RESET)\n"

.PHONY: all libft clean fclean re