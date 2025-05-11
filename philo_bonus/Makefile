SRCS = 	src/main.c \
		src/init.c\
		src/action.c\
		src/monitoring_bonus.c\
		src/philo_routine.c\
		src/cleanup.c \
        src/util.c\
		utils/libft.c\
		utils/parsing.c\

OBJS = $(SRCS:.c=.o)

NAME = philo_bonus

CFLAGS = -Wall -Wextra -Werror -g 
# -pthread -fsanitize=thread 
all: $(NAME)

$(NAME): $(OBJS)
	cc $(CFLAGS) $(OBJS) -o $(NAME) 
	@make clean	
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
