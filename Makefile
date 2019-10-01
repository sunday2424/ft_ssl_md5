# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junpark <junpark@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/01 06:18:52 by junpark           #+#    #+#              #
#    Updated: 2019/10/01 06:47:15 by junpark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl

SRC = $(wildcard *.c)

OBJ = $(SRC:.c=.o)

FT_PRINTF = ft_printf

INCLUDES = ft_ssl.h

CC = gcc -Wall -Wextra -Werror -g

$(NAME):
	make -C $(FT_PRINTF)
	gcc -c -Wall -Werror -Wextra -g $(SRC) -I$(INCLUDES)
	gcc $(OBJ) -L $(FT_PRINTF) -l ftprintf -o $(NAME)

all: $(NAME)

clean:
	@rm -rf $(OBJ)
	@make -C $(FT_PRINTF)/ clean

fclean: clean
	@rm -rf $(NAME) $(OBJ)
	@make -C $(FT_PRINTF)/ fclean

re: fclean all

.PHONY: all clean fclean re
