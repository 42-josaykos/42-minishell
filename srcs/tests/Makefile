NAME 			= tests
LIBFT 		= ../../libft/libft.a

SRC 			= tokenizer.c \
						ast.c

OBJ 			= $(SRC:.c=.o)
INCLUDES 	= -I../../includes -I../../libft
RM 				= rm -rf
CC 				= clang
MEM				= -g -O3 -fsanitize=address

all:	$(NAME)

$(NAME): $(OBJ)
	make -C ../../libft/ 1>/dev/null
	@echo "$(GREEN)$(LIBFT) done...$(END)"
	$(CC) -Wall -Wextra -Werror $(OBJ) $(INCLUDES) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) -Wall -Wextra -Werror $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJ)
	make clean -C ../../libft/ 1>/dev/null

fclean:		clean
	$(RM) $(NAME) a.out vgcore.*
	make fclean -C ../../libft/ 1>/dev/null

re: clean fclean all