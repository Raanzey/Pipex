NAME 		= pipex
CC		= cc
CFLAGS 		= -Wall -Wextra -Werror 
SRCS		= pipex.c pipex_utils.c \
		  

LIBFT		= libft/libft.a
DIR_LIBFT	= libft

all: $(NAME)

$(NAME): $(SRCS)
	make -s -C $(DIR_LIBFT)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) -o $(NAME)

clean:
	make -s -C $(DIR_LIBFT) clean

fclean: clean
	rm -f $(NAME)
	make -s -C $(DIR_LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re 