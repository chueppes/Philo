NAME = philo

SRC = main.c functions.c tools.c routine.c aux_functions.c

OBJ = $(SRC:.c=.o)

PTHREAD = -pthread

%.o: %.c
		@ cc -Wall -Wextra -Werror -c -g $< -o $@

$(NAME): $(OBJ)
		@ cc $(OBJ) $(PTHREAD) -o $(NAME)
		@echo ">> Philosophers Compiled 🍝"

all: $(NAME)

clean:
		@ rm -f $(OBJ)
		@echo ">> All clean 🗑️"

fclean: clean	
		@ rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
