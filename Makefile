# MAKEFILE : ft_ssl_md5

NAME = ft_ssl_md5

SRC += main.c

OBJ = $(SRC:.c=.o)

CC = gcc -Wall -Wextra -Werror

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME) $(OBJ) 

re: fclean $(NAME)
