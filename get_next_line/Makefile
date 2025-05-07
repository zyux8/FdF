# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/10 22:24:49 by ohaker            #+#    #+#              #
#    Updated: 2025/04/29 16:58:04 by ohaker           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line.a
CFLAGS  = -Wall -Wextra -Werror
OBJ = $(SRC:.c=.o)
SRC = get_next_line.c \
	get_next_line_utils.c
# LIBFT_DIR = ../libft
# LIBFT = -L$(LIBFT_DIR) -lft 

.SILENT:

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	# @gcc $(CFLAGS) $(OBJ) -o $(NAME)
	# @rm $(OBJ)

%.o: %.c
	@gcc $(CFLAGS) -c $< -o $@
	# @gcc $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

clean:
	@rm -rf $(OBJ)	

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re