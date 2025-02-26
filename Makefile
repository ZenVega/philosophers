SRC_FOLDER	= philo/

CFILES		= \
			$(SRC_FOLDER)/main.c\
			$(SRC_FOLDER)/utils/utils.c\
			$(SRC_FOLDER)/init/init.c\

OFILES 		= $(CFILES:.c=.o)

CC			= gcc

CFLAGS		= -g -Wall -Wextra -Werror

NAME		= philo

all: $(NAME) 

$(NAME): $(OFILES)
	$(CC) $(CFLAGS) -o $(SRC_FOLDER)$(NAME) $(OFILES)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -g -c $< -o $@

clean:
	rm -f $(OFILES)
	find $(SRC_FOLDER) -name "*.o" -delete

fclean:	clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
