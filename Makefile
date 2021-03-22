# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alpascal <alpascal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/30 11:38:29 by jonny             #+#    #+#              #
#    Updated: 2021/03/22 14:18:29 by alpascal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
GREEN = `tput setaf 2`
RED = `tput setaf 1`
END = `tput sgr0`

NAME 			= minishell
LIBFT 		= libft/libft.a

INCLUDES 	= -Iincludes -Ilibft

SRC_NAME	=	main.c \
						builtins/cd.c \
						builtins/echo.c \
						builtins/env.c \
						builtins/exit.c \
						builtins/export.c \
						builtins/init_env_lst.c \
						builtins/pwd.c \
						builtins/unset.c\
						execs/exec_builtin.c \
						execs/exec_cmd.c \
						execs/exec_piped_cmd.c \
						history/history.c \
						parsing/interpreter.c \
						parsing/parse_cmdline.c \
						parsing/parse_path.c \
						parsing/parse_pipe.c \
						parsing/parse_semicolon.c \
						redirection/fds_handlers.c \
						redirection/fds_redir.c \
						redirection/redirection.c \
						termcap/termcap.c \
						termcap/readline.c \
						tokenizer/tokenizer.c \
						tokenizer/ast.c \
						tokenizer/ast_type.c \
						utils/fork_utils.c \
						utils/free_utils.c \
						utils/list_utils.c \
						utils/string_utils.c \
						utils/string_utils2.c \
						utils/error.c \
						utils/file_status.c \
						utils/signal.c \

OBJ 			= $(SRC:.c=.o)
SRCS_PATH = srcs

SRC 			= $(addprefix $(SRCS_PATH)/,$(SRC_NAME))
RM 				= rm -rf
CC 				= clang
MEM				= -g -O3 -fsanitize=address

all:	$(NAME)

$(NAME): $(OBJ)
	make -C libft/ 1>/dev/null
	@echo "$(GREEN)$(LIBFT) done...$(END)"
	$(CC) -Wall -Wextra -Werror $(OBJ) $(INCLUDES) $(LIBFT) -o $(NAME) -lncurses
	@echo "$(GREEN)$(NAME) binary is ready !$(END)"

%.o: %.c
	@echo "$(GREEN)Compiling source files to objects $<$ ...$(END)"
	$(CC) -Wall -Wextra -Werror $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJ)
	make clean -C libft/ 1>/dev/null

fclean:		clean
	$(RM) $(NAME) a.out vgcore.*
	make fclean -C libft/ 1>/dev/null
	@echo "$(RED)$(LIBFT) removed$(END)"
	@echo "$(RED)$(NAME) removed$(END)"

re: clean fclean all
