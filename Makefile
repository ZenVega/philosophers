SRC_FOLDER	= philo/

MAP = basictest

CFILES		= \
			main.c\
			$(SRC_FOLDER)viewport.c\

OFILES 		= $(CFILES:.c=.o)

LIBFT_PATH	= libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)

INC			= \
			-I ./$(LIBFT_PATH)\

DEPS		= includes/main.h\

CC			= gcc

CFLAGS		= -g -Wall -Wextra -Werror

NAME		= philo

all: $(NAME) 

$(NAME): $(OFILES) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OFILES) $(LIBFT) $(INC)

$(LIBFT):
	$(MAKE) bonus -C $(LIBFT_PATH)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -I/usr/include $(INC) -g -c $< -o $@

clean:
	rm -f $(OFILES)
	find $(SRC_FOLDER) -name "*.o" -delete
	$(MAKE) -C $(LIBFT_PATH) clean

fclean:	clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re
