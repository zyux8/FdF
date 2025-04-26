# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/24 18:17:18 by ohaker            #+#    #+#              #
#    Updated: 2025/04/26 21:49:07 by ohaker           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CFLAGS = -Wall -Wextra -O3 -Iincludes -I/usr/include -Iminilibx-linux
SRC = $(addprefix src/, \
	main.c \
	utils.c )
	
OBJ = $(SRC:.c=.o)
	
# Color definitions for terminal output
NONE		= \033[0m
GREEN		= \033[32;01m
RED			= \033[31;01m
ORANGE		= \033[33;01m

.SILENT:

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(ORANGE)		- Compiling $(NAME)...$(NONE)"
	@make -C minilibx-linux --silent
	@make -C libft --silent
	@make -C get_next_line --silent
	@gcc $(CFLAGS) $(OBJ) libft/libft.a get_next_line/get_next_line.a -Lminilibx-linux -lmlx -lXext -lX11 -lm -o $(NAME) 
	@echo "$(GREEN)		- $(NAME) Compiled -$(NONE)"
	# @rm $(OBJ)
	# @echo "$(ORANGE)		- Deleted object files$(NONE)"

%.o: %.c
	@gcc $(CFLAGS) -c $< -o $@

clean:
	@make clean -C minilibx-linux
	@make clean -C libft
	@make clean -C get_next_line
	@rm -rf $(OBJ)

fclean: clean
	@make fclean -C minilibx-linux
	@make fclean -C libft
	@make fclean -C get_next_line
	@rm -rf $(NAME)

re: fclean all

mygit:
	@git add .
	@git status
	@echo "$(ORANGE)		- Waiting for commit message...$(NONE)"
	@echo "Enter commit message:"; \
	read input; \
	git commit -m "$$input"
	@git push origin main
	@echo "$(GREEN)		- Pushed to git$(NONE)"



.PHONY: all clean fclean re mygit