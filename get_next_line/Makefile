# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/10 22:24:49 by ohaker            #+#    #+#              #
#    Updated: 2025/05/12 18:26:03 by ohaker           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line.a
CFLAGS  = -Wall -Wextra -Werror
SRC = get_next_line.c \
	get_next_line_utils.c
OBJ = $(SRC:.c=.o)

.SILENT:

%.o: %.c
	@gcc $(CFLAGS) -c $< -o $@
	
all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	# @gcc $(CFLAGS) $(OBJ) -o $(NAME)
	# @rm $(OBJ)

clean:
	@rm -rf $(OBJ)	

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re