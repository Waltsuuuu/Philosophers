CC		= cc
CFLAGS	= -Wall -Wextra -Werror
NAME	= philo
INCS	= -I includes
SRC		=	src/00_main.c				\
			src/01_routine.c			\
			src/02_monitor.c 			\
			src/utils/cleanup.c			\
			src/utils/cleanup_utils.c	\
			src/utils/get_set_utils.c	\
			src/utils/timing.c			\
			src/utils/utils.c
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
