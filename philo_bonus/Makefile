SRCS = 	src/main.c \
		src/init.c\
		src/action.c\
		src/monitoring_bonus.c\
		src/philo_routine.c\
		src/cleanup.c \
        src/util.c\
		utils/libft.c\
		utils/parsing.c\
		utils/ft_itoa.c\
		utils/libft_helper.c\

OBJS = $(SRCS:.c=.o)

NAME = philo_bonus

CFLAGS = -Wall -Wextra -Werror -g
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
