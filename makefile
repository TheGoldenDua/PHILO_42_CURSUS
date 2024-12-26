# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: del-ganb <del-ganb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/26 06:01:40 by del-ganb          #+#    #+#              #
#    Updated: 2024/12/26 06:37:32 by del-ganb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread

SRCS = init.c \
       m_utils.c \
       main.c \
       philo_act_utils.c \
       philo_act_utils1.c \
       philo_action.c \
       philos.c \
       tasks.c \
       tasks_utils.c \
       tasks_utils1.c \
       init_utils.c \

OBJS = $(SRCS:.c=.o)
NAME = philo

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.SECONDARY: $(OBJS)
.PHONY: all clean fclean re
