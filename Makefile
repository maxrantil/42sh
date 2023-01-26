# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/12 06:01:22 by mbarutel          #+#    #+#              #
#    Updated: 2023/01/26 10:30:34 by mrantil          ###   ########.fr        #
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
#LEAK_CHECK			+=	-fsanitize=address

UNAME				= $(shell uname)
ifeq ($(UNAME), Darwin)
CFLAGS				+= 	-Werror
endif
ifeq ($(UNAME), Linux)
TERMCAP				=	-lncurses
endif

SOURCES 		= 	sources
INCLUDES		= 	includes/
LIBRARIES 		= 	libft/
BANNER			= 	banner/
BUILDTREE		=	build_tree/
BUILTIN			= 	builtins/
BUILTIN_UTILS	= 	builtin_utils/
EXECTREE		=	exec_tree/
EXPANSION		=	expansion/
HISTORY			= 	history/
INITIALIZE		=	initialize/
KEYBOARD		= 	keyboard/
LEXER			= 	lexer/
MAIN			= 	main/
SIGNALS			= 	signals/
OBJECTS 		= 	objects
TERMIOS			= 	termios/
TOKENIZER		=	tokenizer/
UTILITIES		=	utilities/
FC				= 	fc/
INTERN_VARS		=	intern_variables/
PARAM_FORM		=	parameter_formatting/
FT_TEST			=	ft_test/
HASH			= 	hash/

SOURCE_COUNT = $(words $(FILES))

H_FILES 	= 	ft_42sh \
				keyboard \

FILES			= $(KEYBOARD)ft_add_nl_last_row \
				$(KEYBOARD)ft_add_nl_mid_row \
				$(KEYBOARD)ft_alt_mv \
				$(KEYBOARD)ft_arrow_input \
				$(KEYBOARD)ft_backspace \
				$(KEYBOARD)ft_bslash_escape_check \
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
				$(BANNER)ft_banner \
				$(MAIN)main \
				$(MAIN)shell_end_cycle \
				$(MAIN)reset_fd \
				$(SIGNALS)sig_session_handler \
				$(SIGNALS)set_signal_fork \
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
				$(EXPANSION)ft_expansion \
				$(EXPANSION)ft_expansion_utils \
				$(EXPANSION)ft_expansion_dollar \
				$(EXPANSION)ft_expansion_tilde \
				$(EXPANSION)ft_expansion_excla \
				$(UTILITIES)ft_env_get \
				$(UTILITIES)ft_err_print \
				$(UTILITIES)ft_bslash_check \
				$(UTILITIES)free_node \
				$(BUILTIN)ft_builtins \
				$(BUILTIN)ft_cd \
				$(BUILTIN)ft_echo \
				$(BUILTIN)ft_set \
				$(BUILTIN)ft_exit \
				$(BUILTIN)ft_export \
				$(BUILTIN)ft_unset \
				$(BUILTIN_UTILS)ft_cd_addr_check \
				$(BUILTIN_UTILS)ft_dir_change \
				$(BUILTIN_UTILS)ft_env_append \
				$(BUILTIN_UTILS)ft_env_remove \
				$(BUILTIN_UTILS)ft_env_replace \
				$(BUILTIN_UTILS)ft_env_temp \
				$(TERMIOS)ft_getent \
				$(TERMIOS)ft_raw_disable \
				$(TERMIOS)ft_raw_enable \
				$(INITIALIZE)ft_env_init \
				$(INITIALIZE)ft_init_signals \
				$(INITIALIZE)ft_init_window_size \
				$(INITIALIZE)ft_session_init \
				$(HISTORY)ft_history \
				$(HISTORY)ft_history_get \
				$(HISTORY)ft_history_expansion \
				$(HISTORY)ft_history_write_to_file \
				$(FC)ft_fc \
				$(FC)fc_print_error \
				$(FC)fc_check_flags \
				$(FC)fc_overwrite_fc_cmd_with_prev_cmd \
				$(INTERN_VARS)ft_variables \
				$(INTERN_VARS)add_var \
				$(INTERN_VARS)ft_var_get \
				$(PARAM_FORM)parameter_format \
				$(FT_TEST)ft_test \
				$(FT_TEST)ft_test_is_unary \
				$(FT_TEST)ft_test_is_binary \
				$(HASH)ft_hash \
				$(HASH)hash_init \
				$(HASH)hash_print \
				$(HASH)hash_function \
				$(HASH)hash_init_struct \
				$(HASH)hash_check \
				$(HASH)hash_free \

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
	@mkdir -p $(OBJECTS)/$(KEYBOARD)
	@mkdir -p $(OBJECTS)/$(LEXER)
	@mkdir -p $(OBJECTS)/$(BANNER)
	@mkdir -p $(OBJECTS)/$(MAIN)
	@mkdir -p $(OBJECTS)/$(TOKENIZER)
	@mkdir -p $(OBJECTS)/$(BUILDTREE)
	@mkdir -p $(OBJECTS)/$(EXECTREE)
	@mkdir -p $(OBJECTS)/$(EXPANSION)
	@mkdir -p $(OBJECTS)/$(INITIALIZE)
	@mkdir -p $(OBJECTS)/$(UTILITIES)
	@mkdir -p $(OBJECTS)/$(BUILTIN)
	@mkdir -p $(OBJECTS)/$(BUILTIN_UTILS)
	@mkdir -p $(OBJECTS)/$(TERMIOS)
	@mkdir -p $(OBJECTS)/$(HISTORY)
	@mkdir -p $(OBJECTS)/$(SIGNALS)
	@mkdir -p $(OBJECTS)/$(FC)
	@mkdir -p $(OBJECTS)/$(INTERN_VARS)
	@mkdir -p $(OBJECTS)/$(PARAM_FORM)
	@mkdir -p $(OBJECTS)/$(FT_TEST)
	@mkdir -p $(OBJECTS)/$(HASH)
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