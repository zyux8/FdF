# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/24 18:17:18 by ohaker            #+#    #+#              #
#    Updated: 2025/05/12 17:57:32 by ohaker           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CFLAGS = -Wall -Wextra -Werror -O3 -Iincludes -I/usr/include -Iminilibx-linux
LIBFT_DIR = libft
GNL_DIR = get_next_line
PRINTF_DIR = ft_printf
MLX_DIR = minilibx-linux
LIBFT = libft/libft.a
GNL = get_next_line/get_next_line.a
PRINTF = ft_printf/ftprintf.a
SRC = $(addprefix src/, \
	cleanup.c \
	draw_utils.c \
	handler.c \
	main.c \
	map_parser.c \
	projection.c \
	render.c)
	
OBJ = $(SRC:.c=.o)
	
# Color definitions for terminal output
NONE		= \033[0m
GREEN		= \033[32;01m
RED			= \033[31;01m
ORANGE		= \033[33;01m

.SILENT:

all:	$(NAME)

$(NAME): $(OBJ)
	@echo "$(ORANGE)		- Compiling $(NAME)...$(NONE)"
	@make -C libft --silent
	@make -C get_next_line --silent
	@make -C ft_printf --silent
	@make -C minilibx-linux --silent
	@gcc $(CFLAGS) -I$(LIBFT_DIR) -I$(GNL_DIR) -I$(PRINTF_DIR) -I$(MLX_DIR) $(OBJ) $(GNL) $(LIBFT) $(PRINTF) -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -o $(NAME)
	@echo "$(GREEN)		- $(NAME) Compiled -$(NONE)"

%.o: %.c
	@gcc $(CFLAGS) -c $< -o $@

clean:
	@make clean -C minilibx-linux
	@make clean -C libft
	@make clean -C get_next_line
	@make clean -C ft_printf
	@rm -rf $(OBJ)
	@echo "$(ORANGE)		- Deleted object files$(NONE)"

fclean: clean
	@make fclean -C libft
	@make fclean -C get_next_line
	@make fclean -C ft_printf
	@rm -f $(NAME)
	@echo "$(ORANGE)		- Deleted $(NAME)$(NONE)"

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
		git commit -m "$$input" -m "Commit date: $$TIMESTAMP"; \
		git push origin main; \
		echo "$(GREEN)		- Pushed to git$(NONE)"; \
	fi

.PHONY: all clean fclean re mygit