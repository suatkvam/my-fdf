# Name of the final executable
NAME = fdf

# Directories

# Directory for compiled object files (.o)
OBJ_DIR = obj

# Paths to the external libraries
LIBFT_DIR = libft
MLX_DIR = minilibx
FT_PRINTF_DIR = ft_printf

# source files

EVENT_SRC= key_handle.c close_window.c
PARSER_SRC= open_file.c path_utils.c read_file.c count_cells.c check_map_validation.c map_parser.c map_parser_utils.c parse_token.c free_map.c
RENDER_SRC= init_render.c destroy_render.c draw_line.c draw_line_utils.c put_pixel.c clear_image.c start_render.c project_point.c projection_utils.c scale_utils.c render_map.c map_specific_factors.c
UTILS_SRC= ft_free_split.c atoi_base.c angle_utils.c
COLOR_SRC= color_blend.c

SRCS = $(addprefix utils/, $(UTILS_SRC)) \
	 $(addprefix parser/, $(PARSER_SRC)) \
	 $(addprefix render/, $(RENDER_SRC)) \
	 $(addprefix events/, $(EVENT_SRC)) \
	 $(addprefix colors/, $(COLOR_SRC)) \
	 get-next-line/get_next_line.c \
	 get-next-line/get_next_line_utils.c \
	 main.c

# Automatically generate the object file paths.
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# libraries

LIBFT_LIB = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft
FT_PRINTF_LIB = $(FT_PRINTF_DIR)/libftprintf.a
FT_PRINTF_FLAGS = -L$(FT_PRINTF_DIR) -lftprintf

MLX_GIT_URL = https://github.com/42Paris/minilibx-linux.git
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

# compiler and flags

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDE_FLAGS = -I./includes -I./get-next-line -I./libft -I./ft_printf -I./minilibx -I./parser -I./utils -I./render -I./events -I./colors -I./error
CFLAGS += -g3
CFLAGS += $(INCLUDE_FLAGS)

RM = rm -f
SILENT = @

# rules

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB) $(FT_PRINTF_LIB) $(MLX_LIB)
	@echo "Linking $(NAME)..."
	@$(CC) $(OBJS) $(LIBFT_FLAGS) $(FT_PRINTF_FLAGS) $(MLX_FLAGS) -o $(NAME)
	@echo "\033[32mSuccessfully built $(NAME)!\033[0m"

$(OBJ_DIR)/%.o: %.c $(LIBFT_LIB) $(FT_PRINTF_LIB) $(MLX_LIB)
	@mkdir -p $(@D)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@


$(LIBFT_LIB):
	@echo "Building Libft..."
	@make -s -C $(LIBFT_DIR)

$(FT_PRINTF_LIB):
	@echo "Building ft_printf..."
	@make -s -C $(FT_PRINTF_DIR)

$(MLX_LIB):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "MiniLibX not found. Cloning..."; \
		MLX_CLONE_URL="$(MLX_GIT_URL)"; \
		while true; do \
			echo "Attempting to clone from $$MLX_CLONE_URL"; \
			if git clone --depth=1 "$$MLX_CLONE_URL" $(MLX_DIR); then \
				echo "Clone succeeded."; \
				break; \
			fi; \
			echo "Clone failed from: $$MLX_CLONE_URL"; \
			printf "Enter a new Git URL for MiniLibX (or press Enter to abort): "; \
			read NEW_URL || { echo "No input detected. Aborting."; exit 1; }; \
			if [ -z "$$NEW_URL" ]; then echo "Aborted by user."; exit 1; fi; \
			MLX_CLONE_URL="$$NEW_URL"; \
		done; \
		echo "MiniLibX setup complete."; \
	fi
	@echo "Building MiniLibX..."
	@make -s -C $(MLX_DIR)

# clean rule

clean:
	@if [ -d "$(LIBFT_DIR)" ]; then make -s -C $(LIBFT_DIR) clean; fi
	@if [ -d "$(FT_PRINTF_DIR)" ]; then make -s -C $(FT_PRINTF_DIR) clean; fi
	@if [ -d "$(MLX_DIR)" ]; then make -s -C $(MLX_DIR) clean; fi
	@$(RM) -r $(OBJ_DIR)
	@echo "Cleaned object files."

fclean: clean
	@if [ -d "$(LIBFT_DIR)" ]; then make -s -C $(LIBFT_DIR) fclean; fi
	@if [ -d "$(FT_PRINTF_DIR)" ]; then make -s -C $(FT_PRINTF_DIR) fclean; fi
	@$(RM) $(NAME)
	@echo "Removed binary: $(NAME)."

re: fclean all

distclean: fclean
	@$(RM) -r $(MLX_DIR)
	@echo "Removed MiniLibX directory."

.PHONY: all clean fclean re distclean