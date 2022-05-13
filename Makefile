NAME = philo
SRCS = \
	main.c
OBJS = $(SRCS:.c=.o)
FLAGS = -Wall -Werror -Wextra -pthread -g
INC = -I ./inc

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(INC) $(SRCS) -o $(NAME)

%.o: %.c
	$(CC) -c $(INC) $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all