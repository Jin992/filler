# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: earteshc <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/05 12:22:40 by earteshc          #+#    #+#              #
#    Updated: 2018/03/05 12:22:41 by earteshc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = earteshc.filler
CC = @gcc
CFLAGS = -Wall -Wextra -Werror -Ilib/includes

FILLER = main.c

OBJ = $(FILLER:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Compiling libft wait..."
	@make -C ./lib/
	@echo "Compiling ft_ls wait..."
	@gcc -L ./lib/ -lft $(OBJ) -o $(NAME)
	@echo "Done."

clean:
	@make -C ./lib/ clean
	@/bin/rm -f $(OBJ)

fclean: clean
	@make -C ./lib/ fclean
	@/bin/rm -f $(NAME)

re: fclean all
