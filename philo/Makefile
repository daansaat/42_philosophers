NAME = philo
SRCS_DIR = src
OBJS_DIR = obj
SRCS_FILES = \
	main.c \
	init.c \
	process.c \
	utils.c \
	monitor.c
# SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
# SRCS = $(SRCS_FILES)=$(SRCS_DIR)/%.c
OBJS = $(SRCS_FILES:%.c=$(OBJS_DIR)/%.o)
FLAGS = -Wall -Werror -Wextra -pthread
INC = -I ./inc

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $^ -o $@

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p obj
	$(CC) $(INC) -c $< -o $@

clean:
	rm -drf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all