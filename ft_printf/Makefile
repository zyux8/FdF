# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/24 16:34:43 by ohaker            #+#    #+#              #
#    Updated: 2025/05/09 18:58:22 by ohaker           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = ftprintf.a
CFLAGS = -Wall -Wextra -Werror

SRC = \
	ft_printf.c \
	ft_def_format.c \
	ft_print_hex.c \
	ft_print_hex_upp.c \
	ft_putunsignbr.c \
	ft_print_ptr.c \
	ft_putnbry.c \
	ft_putstry.c

OBJ = $(SRC:.c=.o)
# LIBFT_DIR = ../libft
# LIBFT = -L$(LIBFT_DIR) -lft 

%.o: %.c
	@gcc $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

franci:
	clear
	~/francinette/tester.sh
# Testing with francinette. Clears the terminal and starts tester.
# alias francinette="$HOME"/francinette/tester.sh
# alias paco="$HOME"/francinette/tester.sh

mygit:
	@bash -c ' \
	cd ../../GitHub && \
	cp -ru ~/Projects/printf ~/GitHub && \
	git add printf && \
	git status && \
	read -p "Commitment message: " input; \
	git commit -m "$$input" && \
	git push origin main'
# Command to copy all changed files into another directory
# so it can be pushed into my GitHub.

.PHONY: all clean fclean re