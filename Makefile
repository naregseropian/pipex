NAME	= pipex
CC	= cc
CFLAGS	= -Wall -Werror -Wextra

SRCS	= main.c pipex.c pathing.c ft_free.c 

OBJS = $(SRCS:.c=.o)

RM	= rm -f
LIBFT	= libft/libft.a

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) 

clean:
	@make clean -C libft
	$(RM) $(OBJS)

fclean: clean
	@make fclean -C libft
	$(RM) $(NAME)

re: fclean 
	make all

.PHONY: all clean fclean re