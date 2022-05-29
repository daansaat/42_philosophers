NAME = philo_bonus
SRCS_DIR_BONUS = src_bonus/
SRCS_LIST_BONUS = \
	main_bonus.c \
	utils_bonus.c \
	init_bonus.c \
	child_bonus.c \
	parent_bonus.c
SRCS_BONUS = $(addprefix $(SRCS_DIR_BONUS), $(SRCS_LIST_BONUS))
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
FLAGS = -Wall -Werror -Wextra -pthread
INC_BONUS = -I ./inc_bonus

all: $(NAME)

$(NAME): $(OBJS_BONUS)
	$(CC) $(FLAGS) $(INC_BONUS) $(SRCS_BONUS) -o $(NAME)

%.o: %.c
	$(CC) -c $(INC_BONUS) $< -o $@

clean:
	rm -f $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all