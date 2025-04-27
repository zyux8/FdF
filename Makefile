# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/24 18:17:18 by ohaker            #+#    #+#              #
#    Updated: 2025/04/27 15:09:11 by ohaker           ###   ########.fr        #
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
	@make -C libft --silent
	@make -C get_next_line --silent
	@make -C minilibx-linux --silent
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
	@rm -f $(NAME)

re: fclean all

mygit:
	@git add .
	@git status
	@echo "$(ORANGE)		- Enter commit message:$(NONE)"; \
	read input; \
	if [ -z "$$input" ]; then \
		echo "$(RED)		- No commit message entered. Exiting.$(NONE)"; \
	else \
		TIMESTAMP=$$(date '+%Y-%m-%d %H:%M'); \
		git commit -m "$$input\nCommit date: $$TIMESTAMP"; \
		git push origin main; \
		echo "$(GREEN)		- Pushed to git$(NONE)"; \
	fi

.PHONY: all clean fclean re mygit