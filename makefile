
NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread

SRC_DIR = ./
OBJ_DIR = ./objs

SRCS = init.c \
       m_utils.c \
       main.c \
       philo_act_utils.c \
       philo_act_utils1.c \
       philo_action.c \
       philos.c \
       tasks.c \
       tasks_utils.c \
       tasks_utils1.c

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

HEADERS = philo.h

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re