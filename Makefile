NAME = philosophers

SRC = philo/main.c philo/functions.c philo/tools.c philo/routine.c philo/aux_functions.c

OBJ = $(SRC:.c=.o)

PTHREAD = -pthread

%.o: %.c
		cc -Wall -Wextra -Werror -c -g $< -o $@

$(NAME): $(OBJ)
		cc $(OBJ) $(PTHREAD) -o $(NAME)

all: $(NAME)

clean:
		rm -f $(OBJ)

fclean: clean	
		rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re