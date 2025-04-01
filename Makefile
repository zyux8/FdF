# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/24 18:17:18 by ohaker            #+#    #+#              #
#    Updated: 2025/03/25 20:20:51 by ohaker           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = FdF
CFLAGS = -Wall -Wextra -Werror
OBJ = $(SRC:.c=.o)

SRC = \
	main.c	

# Path to the MinilibX folder 
MLX_PATH = minilibx-linux
MLX_LIB = $(MLX_PATH)/libmlx.a

# URL to download the MinilibX tarball
MLX_URL = https://cdn.intra.42.fr/document/document/31497/minilibx-linux.tgz

# Path for downloading the tarball
MLX_TAR = inilibx-linux.tgz

	
# Color definitions for terminal output
NO_COLOR      = \033[0m
OK_COLOR      = \033[32;01m
ERROR_COLOR   = \033[31;01m
WARN_COLOR    = \033[33;01m

OK_STRING     = $(OK_COLOR)[OK]$(NO_COLOR)
ERROR_STRING  = $(ERROR_COLOR)[ERROR]$(NO_COLOR)
WARN_STRING   = $(WARN_COLOR)[WARNING]$(NO_COLOR)

.SILENT:

# Check if MinilibX is installed
check_mlx:
	@echo "Checking if MinilibX is installed..."
	@if [ ! -d "$(MLX_PATH)" ]; then \
		echo "$(WARN_STRING)$(WARN_COLOR) MinilibX not found, downloading... $(NO_COLOR)"; \
		$(MAKE) download_mlx; \
	else \
	echo  "$(OK_STRING)$(OK_STRING) MinilibX is already installed.$(NO_COLOR)"; \
	fi

# Download and extract MinilibX if not already present
download_mlx:
	@printf "$(WARN_STRING) $(OK_COLOR)Downloading MinilibX...$(NO_COLOR)\n"
	@mkdir -p $(MLX_PATH)
	@curl -L $(MLX_URL) -o $(MLX_TAR)
	@printf "$(WARN_STRING) $(OK_COLOR)Extracting MinilibX...\n $(NO_COLOR)"
	@tar -xvzf $(MLX_TAR) 
	@rm -f $(MLX_TAR)
	@printf "$(OK_STRING)$(OK_COLOR)MinilibX downloaded and extracted.\n $(NO_COLOR)"

all: $(NAME)

$(NAME): $(OBJ)
	@echo $(BLUE) "		- Compiling $(NAME)..." $(NONE)
	@make re -C libft
	@gcc $(CFLAGS) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME) 
	@echo $(GREEN)"- Compiled -"$(NONE)
	@rm $(OBJ)
	@echo $(BLUE) "		Deleted object files" $(NONE)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

$(OBJ): $(SRC)
	@gcc $(CFLAGS) -c $(SRC)

clean:
	@make clean -C libft
	@rm -rf $(OBJ)

fclean: clean
	@make clean -C mlx/
	@make fclean -C libft
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re download_mlx check_mlx