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
INC = -I ./inc -I ./libft
LIB = -L ./libft -l ft

all: $(NAME)

$(NAME): libft/libft.a $(OBJS)
	$(CC) $(FLAGS) $(INC) $(LIB) $(SRCS) -o $(NAME)

%.o: %.c
	$(CC) -c $(INC) $< -o $@

libft/libft.a: 
	make -C libft

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	rm -f libft/libft.a

re: fclean all