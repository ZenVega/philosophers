SRC_FOLDER	= philo/
NP = 5		#num_of_phils
NM = 30		#num_of_meals
TE = 30		#time_to_eat
TD = 60		#time_to_die
TS = 20		#time_to_sleep

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

SANITIZER = -fsanitize=address

SANITIZER_OFF = 

NAME		= philo

all: $(NAME) 

$(NAME): $(OFILES)
	$(CC) $(CFLAGS) $(SANITIZER_OFF) -o $(SRC_FOLDER)$(NAME) $(OFILES)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) $(SANITIZER_OFF) -I/usr/include -g -c $< -o $@

clean:
	rm -f $(OFILES)
	find $(SRC_FOLDER) -name "*.o" -delete

fclean:	clean
	rm -f $(NAME)/$(NAME)

# ./prog num_of_phils time_to_die time_to_eat time_to_sleep [each_must eat]
test: $(NAME)
	$(SRC_FOLDER)$(NAME) $(NP) $(TD) $(TE) $(TS) $(NM)

debug: $(NAME)
	gdb --args $(SRC_FOLDER)$(NAME) $(NP) $(TD) $(TE) $(TS) $(NM)

re: fclean all

.PHONY: all clean fclean re
