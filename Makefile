NAME = philo
SRCS_DIR = src/
SRCS_LIST = \
	main.c \
	init.c \
	process.c \
	utils.c \
	monitor.c
SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LIST))
OBJS = $(SRCS:.c=.o)
FLAGS = -Wall -Werror -Wextra -pthread -g
INC = -I ./inc

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(INC) $(LIB) $(SRCS) -o $(NAME)

%.o: %.c
	$(CC) -c $(INC) $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all