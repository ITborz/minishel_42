# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bkristen <bkristen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/08 19:16:05 by bkristen          #+#    #+#              #
#    Updated: 2022/09/26 17:18:27 by bkristen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

SRC			=	main.c\
				parser/merge_parts/merge_parts_util.c\
				parser/merge_parts/merge_parts.c\
				parser/tokenizer/token_type_error.c\
				parser/tokenizer/specify_token.c\
				parser/tokenizer/tokenizer.c\
				parser/tokenizer/redir_assignment.c\
				parser/editing_tokens/editing_tokens_util.c\
				parser/editing_tokens/editing_tokens.c\
				parser/editing_tokens/handle_env_util.c\
				parser/editing_tokens/handle_env.c\
				parser/editing_tokens/env_init.c\
				parser/error_cmd.c\
				parser/parser_utilities.c\
				parser/parsing_main.c\
				executor/exec.c\
				executor/export_1.c\
				executor/find_path.c\
				executor/ft_builtin.c\
				executor/redir_heredoc.c\
				executor/init_export.c\
				executor/handle_cd.c\
				executor/handle_echo.c\
				executor/handle_env.c\
				executor/handle_exit.c\
				executor/ms_init_env.c\
				executor/ms_pwd.c\
				executor/ms_unset.c\
				executor/file_open.c\
				executor/signal.c\
				executor/sort.c\

HEADER		=	minishell.h

CC			=	cc

FLAGS		= -Wall -Werror -Wextra -I$(HEADER) -I/Users/$(USER)/.brew/Cellar/readline/8.1.2/include

RM			=	rm -f

OBJ			= $(SRC:.c=.o)

all : libft $(NAME)
	stty -ctlecho
$(NAME) : $(OBJ) 
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) -L/Users/$(USER)/.brew/Cellar/readline/8.1.2/lib/ -lreadline -L./libft -lft

%.o: %.c $(HEADER) Makefile
	$(CC) $(FLAGS) -c $< -o $@

libft :
	make -C libft

clean :
	make -C libft clean
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)
	$(RM) libft/libft.a

re : fclean all

.PHONY: all clean fclean re libft