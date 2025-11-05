CC		= cc
CFLAGS	= -Wall -Wextra -Werror
NAME	= philo
INCS	= -I includes
SRC		=	src/main.c			\
			src/routine.c		\
			src/monitor.c 		\
			src/utils.c 		\
			src/get_set_utils.c	\
			src/cleanup.c		\
			src/cleanup_utils.c
OBJS	= $(SRC:.c=.o)

.SECONDARY: all

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
