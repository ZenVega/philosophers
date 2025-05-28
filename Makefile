SRC_FOLDER	= philo/
NP = 11		#num_of_phils
NM = 30		#num_of_meals
TE = 200	#time_to_eat
TD = 450		#time_to_die
TS = 100		#time_to_sleep

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

_SANITIZER = -fsanitize=thread

CFLAGS		= -g -Wall -Wextra -Werror -pthread $(SANITIZER)

VALGRIND_FLAGS= \
				--track-origins=yes
				--leak-check=full
				--show-leak-kinds=all

NAME		= philo

all: $(NAME) 

$(NAME): $(OFILES)
	$(CC) $(CFLAGS) $(SANITIZER) -o $(SRC_FOLDER)$(NAME) $(OFILES)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) $(SANITIZER) -I/usr/include -g -c $< -o $@

clean:
	rm -f $(OFILES)
	find $(SRC_FOLDER) -name "*.o" -delete

fclean:	clean
	rm -f $(NAME)/$(NAME)

# ./prog num_of_phils time_to_die time_to_eat time_to_sleep [each_must eat]
test_live: $(NAME)
	$(SRC_FOLDER)$(NAME) 7 600 200 100 30

test_die: $(NAME)
	$(SRC_FOLDER)$(NAME) 7 360 200 200 30

val_test: $(NAME)
	valgrind $(VALGRIND_FLAGS) $(SRC_FOLDER)$(NAME) 5 220 100 100 5

debug: $(NAME)
	gdb --args $(SRC_FOLDER)$(NAME) $(NP) $(TD) $(TE) $(TS) $(NM)

re: fclean all

.PHONY: all clean fclean re
