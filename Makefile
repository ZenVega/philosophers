SRC_FOLDER	= philo/
NP = 5

CFILES		= \
			$(SRC_FOLDER)/main.c\
			$(SRC_FOLDER)/utils/utils.c\
			$(SRC_FOLDER)/init/init.c\
			$(SRC_FOLDER)/philosopher/philosopher.c\
			$(SRC_FOLDER)/philosopher/phil_utils.c\
			$(SRC_FOLDER)/supervision/supervision.c\

OFILES 		= $(CFILES:.c=.o)

DEPS		= \
			  includes/main.h\
			  includes/constants.h
CC			= gcc

CFLAGS		= -g -Wall -Wextra -Werror -pthread

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

# ./prog num_of_phils time_to_die time_to_eat time_to_sleep [each_must eat]
test: $(NAME)
	philo/philo $(NP) 1000 100 100 20

debug: $(NAME)
	gdb --args philo/philo $(NP) 1000 100 100 20

re: fclean all

.PHONY: all clean fclean re
