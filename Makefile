# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/20 17:04:36 by schoe             #+#    #+#              #
#    Updated: 2022/07/20 12:48:43 by schoe            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Werror -Wextra -Iincludes
CC = cc

READLINE_LIB 	= -lreadline -L /Users/$(USER)/.brew/opt/readline/lib
READLINE_INC	= -I /Users/$(USER)/.brew/opt/readline/include

SRCS = srcs/main.c srcs/ft_cmd.c srcs/ft_parsing.c srcs/ft_error_check.c \
	   srcs/ft_pipe_utils.c srcs/ft_pipe.c srcs/ft_dire_file.c srcs/ft_utils.c \
	   srcs/ft_echo.c srcs/ft_free.c srcs/ft_syntax.c srcs/ft_trans_quot.c \
	   srcs/ft_make_here_doc.c srcs/ft_error_check_exit.c srcs/ft_parsing_sep.c \
	   srcs/ft_syntax_utils.c srcs/ft_builtin.c srcs/ft_main_utils.c \
	   srcs/ft_exit.c

S_SRCS = srcs/cd/change_directory.c \
		srcs/cd/cd_utils.c \
		srcs/env/env.c \
		srcs/env/unset.c \
		srcs/env/export.c \
		srcs/env/env_arr.c \
		srcs/env/export_utils.c \
		srcs/env/print_env_export.c \
		srcs/quote/quote.c \
		srcs/quote/quote_utils.c \
		srcs/quote/quote_str_utils.c \
		srcs/quote/quote_find_utils.c \
		srcs/utils.c \

LIBFT = libft.a

NAME = minishell

C_OBJS = $(SRCS:.c=.o)
S_OBJS = $(S_SRCS:.c=.o)

OBJS = $(C_OBJS) $(S_OBJS)

all:  $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(READLINE_INC) $(READLINE_LIB)

$(LIBFT):
	make -C ./libft

%.o: %.c
	$(CC) $(CFLAGS) $(READLINE_INC) -c $< -o $@

clean:
	make clean -C libft/
	rm -rf $(OBJS)

fclean: clean
	make fclean -C libft/
	rm -rf $(NAME) $(OBJS)

re :	
	${MAKE} fclean 
	${MAKE} all

.PHONY: all clean fclean re
