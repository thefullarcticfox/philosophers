NAME = philo_three
SRC = main.c ft_tools.c ft_error.c ft_initphilo.c ft_runphilo.c ft_philowatch.c
OBJ = $(SRC:.c=.o)
INCLUDEDIR = ./
HEADERS = $(INCLUDEDIR)philo_three.h
CC = clang
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDEDIR)
EXECFLAGS = $(CFLAGS) -pthread

.PHONY: all bonus clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(EXECFLAGS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
