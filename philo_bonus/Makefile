NAME = philo_bonus
SRC =	srcs/ft_libs.c \
		srcs/take_params.c \
		srcs/sem.c \
		srcs/thread_process.c \
		srcs/chrono.c \
		srcs/init.c \
		srcs/exit.c \
		srcs/main.c
HEADERS = headers/phil_bonus.h
OBJ = $(SRC:.c=.o)
LIBS = -pthread
FLAGS = -Wall -Wextra -Werror -std=c99 -g

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
