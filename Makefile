# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jonny <josaykos@student.42.fr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/30 11:38:29 by jonny             #+#    #+#              #
#    Updated: 2020/11/30 11:58:27 by jonny            ###   ########.fr        #
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

OBJ 			= $(SRC:.c=.o)
SRCS_PATH = srcs

SRC 			= $(addprefix $(SRCS_PATH)/,$(SRC_NAME))
RM 				= rm -rf
CC 				= clang

all:	$(NAME)

$(NAME): $(OBJ)
	make -C libft/ 1>/dev/null
	@echo "$(GREEN)$(LIBFT) done...$(END)"
	$(CC) $(OBJ) $(INCLUDES) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)$(NAME) binary is ready !$(END)"

%.o: %.c
	@echo "$(GREEN)Compiling source files to objects $<$ ...$(END)"
	$(CC) -Wall -Wextra -Werror $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean:		clean
	$(RM) $(NAME)
	make fclean -C libft/ 1>/dev/null
	@echo "$(RED)$(LIBFT) removed$(END)"
	@echo "$(RED)$(NAME) removed$(END)"

re: clean fclean all
