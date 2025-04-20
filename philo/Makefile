SRCS = 	src/main.c \
		utils/libft.c\
		utils/parsing.c\

OBJS = $(SRCS:.c=.o)

NAME = philo

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	cc $(CFLAGS) $(OBJS) -o $(NAME) -g
	@make clean

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
