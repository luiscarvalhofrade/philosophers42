# compiler
CC = cc

# flags and header
CFLAGS = -Werror -Wall -Wextra -I .

# program name
NAME =	philo

# source files
SRC = 	init.c \
		philo.c \
		monitor.c \
		routine.c \
		utils.c \
		cleanup.c \

# objects
OBJ = 	 $(SRC:.c=.o)

# rules
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ)
	@echo "Object files cleaned."

fclean:
	@rm -f $(NAME) $(OBJ)
	@echo "Program cleaned."

re: fclean all

.PHONY: all clean fclean re