# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/19 14:58:30 by mbarutel          #+#    #+#              #
#    Updated: 2022/09/12 08:37:58 by mbarutel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#COLORS
SHELL 				:= /bin/bash
GREEN 				= \033[32m
GREEN_BACKGROUND 	= \033[42m
WHITE_BACKGROUND 	= \033[47m
VIOLET_BACKGROUND 	= \033[0;45m
YELLOW_BACKGROUND 	= \033[0;43m
WHITE 				= \033[37m
YELLOW 				= \033[33m
BLACK 				= \033[30m
VIOLET				= \033[35m
RESET 				= \033[0m
RED 				= \033[31m
CYAN 				= \033[36m
BOLD 				= \033[1m

#PRINTING TOOLS
ERASE_LINE 			= \033[K
UP 					= A
DOWN 				= B
RIGHT 				= C
LEFT				= D
MOVE				= \033[
C_INVISIBLE 		= \033[?25l
C_VISIBLE 			= \033[?25h

#FORBID KEYBOARD INTERACT
$(shell stty -echo)

CC					=	gcc
NAME				=	libft.a
MAKEFLAGS			+=	--no-print-directory
CFLAGS				=	-Wall -Wextra -g -O3 -I$(INC_DIR)
TERMCAPS			=	-ltermcap

_SRC_LIBFT		= ft_memset.c ft_atoi.c ft_bzero.c ft_memchr.c ft_memcpy.c ft_memcmp.c ft_strlen.c ft_strdup.c \
				ft_strcpy.c ft_strcat.c ft_strchr.c ft_strstr.c ft_strcmp.c ft_memccpy.c ft_memmove.c ft_strncpy.c \
				ft_strncat.c ft_strlcat.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
				ft_isascii.c ft_isprint.c ft_isspecial.c ft_toupper.c ft_tolower.c ft_memalloc.c ft_memdel.c ft_strnew.c \
				ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c \
				ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_ftoa.c ft_lftoa.c ft_strsep.c ft_itoa.c ft_putstr.c ft_putnbr.c ft_lstnew.c \
				ft_lstdel.c ft_lstadd.c ft_lstmap.c ft_calloc.c ft_putchar.c ft_putendl.c ft_lstiter.c ft_strlcpy.c ft_lstlast.c ft_lstsize.c \
				ft_itoa_base.c ft_ltoa_base.c ft_lstdelone.c ft_putnbr_fd.c ft_putstr_fd.c get_next_line.c ft_putchar_fd.c ft_putendl_fd.c ft_lstaddback.c \
				ft_lltoa_base.c ft_ulltoa_base.c ft_exit_no_mem.c ft_strjoin_head.c ft_strjoin_tail.c ft_isspace.c ft_del.c ft_strndup.c ft_arrlen.c ft_skip_space.c \
				ft_arrclean.c

_SRC_PRINTF		= ft_printf.c ft_utils.c ft_printers.c ft_colouring.c ft_bonus_func.c \
				ft_arg_filter.c ft_str_convert.c ft_char_convert.c ft_printer_utils.c ft_diouxf_convert.c

DIR_LIBFT		= libft/
DIR_PRINTF		= ft_printf/
DIR_VEC			= ft_vec/

_SRC			= $(_SRC_LIBFT) $(_SRC_PRINTF) $(_SRC_VEC)
SOURCE_COUNT 	= $(words $(_SRC))

OBJ_FILES		= $(_SRC:.c=.o)

DIR_OBJS		= objects/
OBJS			= $(patsubst %, $(DIR_OBJS)%, $(_SRC:.c=.o))

INC_DIR			= includes/
_INC			= libft.h ft_printf.h ft_vec.h
INC				= $(addprefix $(INC_DIR), $(_INC))
HEADERS			= -I$(INC_DIR)

ASSERT_OBJECT	= && printf "$(ERASE_LINE)" && printf "$@ $(GREEN)$(BOLD) ✔$(RESET)" || (printf "$@ $(RED)$(BOLD)✘$(RESET)\n" | @printf "$(C_VISIBLE)" && exit 1)

all: $(NAME)

$(NAME): $(DIR_OBJS) $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@printf "Compiled $(BOLD)$(GREEN)$(NAME)$(RESET)!\n\n"
	@stty echo
	@printf "$(C_VISIBLE)"

$(DIR_OBJS):
	@stty -echo
	@mkdir -p $(DIR_OBJS)
	@printf "$(GREEN)_________________________________________________________________\n$(RESET)"
	@printf "$(NAME): $(GREEN)$(DIR_OBJS) directory was created.$(RESET)\n\n\n"

$(DIR_OBJS)%.o: $(DIR_LIBFT)%.c
	@printf "$(C_INVISIBLE)"
	@printf "$(MOVE)2$(UP)"
	@$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $< $(ASSERT_OBJECT)
	@make pbar_libft

$(DIR_OBJS)%.o: $(DIR_PRINTF)%.c
	@printf "$(C_INVISIBLE)"
	@printf "$(MOVE)2$(UP)"
	@$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $< $(ASSERT_OBJECT)
	@make pbar_libft

$(DIR_OBJS)%.o: $(DIR_VEC)%.c
	@printf "$(C_INVISIBLE)"
	@printf "$(MOVE)2$(UP)"
	@$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $< $(ASSERT_OBJECT)
	@make pbar_libft

clean:
	@if [ -d $(DIR_OBJS) ]; then rm -rf $(DIR_OBJS); printf "libft:		$(RED)$(DIR_OBJS) was deleted$(RESET)\n"; fi

fclean: clean
	@if [ -f $(NAME) ]; then rm -f $(NAME); printf "$(NAME):	$(RED)library was deleted$(RESET)\n"; fi

re: fclean all

pbar_libft:
	$(eval LOADED_COUNT = $(words $(wildcard $(DIR_OBJS)*.o)))
	@printf "\r$(MOVE)76$(RIGHT)Files compiled [$(BOLD)$(YELLOW)$(LOADED_COUNT)$(RESET) / $(BOLD)$(YELLOW)$(SOURCE_COUNT)$(RESET)]\n"
	@for ((i = 1; i <= $(LOADED_COUNT) * 100 / $(SOURCE_COUNT); i++)); do\
		printf "$(YELLOW_BACKGROUND) $(RESET)" ;\
	done ;
	@for ((i = 1; i <= 100 - ($(LOADED_COUNT) * 100 / $(SOURCE_COUNT)); i++)); do\
		printf "$(WHITE_BACKGROUND) $(RESET)" ;\
	done ;
	@printf "$(YELLOW_BACKGROUND)$(BOLD)$(WHITE)$(MOVE)55$(LEFT)[$$(($(LOADED_COUNT) * 100 / $(SOURCE_COUNT))).$$(($(LOADED_COUNT) * 1000 / $(SOURCE_COUNT) % 10))%%]$(MOVE)54$(RIGHT)$(RESET)\n"

.PHONY: all clean fclean re

#ALLOW KEYBOARD INTERACT
$(shell stty echo)