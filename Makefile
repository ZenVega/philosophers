SRC_FOLDER	= philo/

CFILES		= \
			$(SRC_FOLDER)/main.c\
			$(SRC_FOLDER)/utils/utils.c\
			$(SRC_FOLDER)/init/init.c\
			$(SRC_FOLDER)/philosopher/philosopher.c\

OFILES 		= $(CFILES:.c=.o)

DEPS		= \
			  includes/main.h\
			  includes/constants.h
CC			= gcc

CFLAGS		= -g -Wall -Wextra -Werror

NAME		= philo

all: $(NAME) 

$(NAME): $(OFILES)
	$(CC) $(CFLAGS) -o $(SRC_FOLDER)$(NAME) $(OFILES)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -I/usr/include -g -c $< -o $@

clean:
	rm -f $(OFILES)
	find $(SRC_FOLDER) -name "*.o" -delete

fclean:	clean
	rm -f $(NAME)/$(NAME)

test: $(NAME)
	philo/philo 5 4 3 2

debug: $(NAME)
	gdb --args philo/philo 5 4 3 2

re: fclean all

.PHONY: all clean fclean re
