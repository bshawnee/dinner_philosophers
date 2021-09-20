# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bshawnee <bshawnee@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/04 13:05:06 by bshawnee          #+#    #+#              #
#    Updated: 2021/07/20 18:45:52 by bshawnee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC =	srcs/init_phil.c \
		srcs/check_input.c \
		srcs/ft_lib.c \
		srcs/threads.c \
		srcs/run.c \
		srcs/exit.c \
		srcs/main.c
HEADERS = headers/phil.h
OBJ = $(SRC:.c=.o)
LIBS = -pthread
FLAGS = -Wall -Wextra -Werror -std=c99

NUMBER_OF_PHILOS = 4
TIME_TO_DIE = 410
TIME_TO_EAT = 200
TIME_TO_SLEEP = 200
PHILOS_MUST_EAT = 2

all: $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	$(CC) $(SRC) $(FLAGS) $(LIBS) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: all
	./$(NAME) $(NUMBER_OF_PHILOS) $(TIME_TO_DIE) $(TIME_TO_EAT) $(TIME_TO_SLEEP) $(PHILOS_MUST_EAT)

leak: all
	leaks -atExit -- ./$(NAME) 4 100 200 200

norm:
	norminette $(SRC) $(HEADERS)
