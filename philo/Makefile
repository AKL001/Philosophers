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

CFLAGS = -Wall -Wextra -Werror -fsanitize=address
# -pthread -fsanitize=thread 
all: $(NAME)

$(NAME): $(OBJS)
	cc $(CFLAGS) $(OBJS) -o $(NAME) 

# gcc -fsanitize=thread -g 
# valgrind --tool=helgrind ./philo <args>
# valgrind --tool=drd ./philo <args>.
%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
