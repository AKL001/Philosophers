SRCS = 	src/main.c \
		src/init.c\
		src/actions.c\
		src/monitor.c\
		src/philo_routine.c\
		src/utils.c\
		utils/libft.c\
		utils/parsing.c\
		src/cleanup.c


OBJS = $(SRCS:.c=.o)

NAME = philo

CFLAGS = -Wall -Wextra -Werror
# -pthread -fsanitize=thread 

all: $(NAME)

$(NAME): $(OBJS)
	cc $(CFLAGS) $(OBJS) -o $(NAME) 

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
