NAME = minirt

SRCS = main.c tuple.c matrix.c color.c transformation.c 
	
OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lm
LIBS= -L ./minilibx-linux -lmlx -lX11 -lXext

all:$(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME) $(LDFLAGS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
.SECONDARY:$(OBJS)
.PHONY : all clean fclean re