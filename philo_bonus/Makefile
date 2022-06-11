NAME = philo_bonus
SRC_DIR = src/
SRC = \
	main_bonus.c \
	utils_bonus.c \
	init_bonus.c \
	child_bonus.c \
	parent_bonus.c
OBJ_DIR = obj/
OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)
FLAGS = -Wall -Werror -Wextra
INC = -I ./inc

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $^ -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) $(INC) -c $< -o $@

clean:
	rm -rdf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all