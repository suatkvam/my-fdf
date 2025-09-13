# Name of the final executable
NAME = fdf

# Directories

# Directory for compiled object files (.o)
OBJ_DIR = obj

# Directories where source files (.c) are located for vpath
SRC_DIRS = srcs srcs/init srcs/parsing srcs/rendering srcs/events srcs/cleanup \
           get-next-line

# Paths to the external libraries
LIBFT_DIR = libft
MLX_DIR = minilibx

# source files

# List all your .c source files here by NAME ONLY.
SRCS = main.c \
       close_window.c \
       key_handle.c \
       get_map_dimensions.c \
       open_file.c \
       draw_line.c \
       get_next_line_bonus.c

# Automatically generate the object file paths.
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# libraries

LIBFT_LIB = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

MLX_URL = https://cdn.intra.42.fr/document/document/34669/minilibx-linux.tgz
MLX_TGZ = minilibx.tgz
MLX_EXTRACTED_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

# compiler and flags

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDE_FLAGS = -I./includes -I./get-next-line -I./libft -I./minilibx
CFLAGS += $(INCLUDE_FLAGS)

RM = rm -f
SILENT = @

# rules

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB) $(MLX_LIB)
	@echo "Linking $(NAME)..."
	@$(CC) $(OBJS) $(LIBFT_FLAGS) $(MLX_FLAGS) -o $(NAME)
	@echo "\033[32mSuccessfully built $(NAME)!\033[0m"

$(OBJ_DIR)/%.o: %.c $(LIBFT_LIB) $(MLX_LIB)
	@mkdir -p $(@D)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

vpath %.c $(SRC_DIRS)

$(LIBFT_LIB):
	@echo "Building Libft..."
	@make -s -C $(LIBFT_DIR)

$(MLX_LIB):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "MiniLibX not found. Downloading..."; \
		wget -q -O $(MLX_TGZ) $(MLX_URL); \
		tar -xzf $(MLX_TGZ); \
		mv $(MLX_EXTRACTED_DIR) $(MLX_DIR); \
		rm -f $(MLX_TGZ); \
		echo "MiniLibX setup complete."; \
	fi
	@echo "Building MiniLibX..."
	@make -s -C $(MLX_DIR)

# clean rule

clean:
	@if [ -d "$(LIBFT_DIR)" ]; then make -s -C $(LIBFT_DIR) clean; fi
	@if [ -d "$(MLX_DIR)" ]; then make -s -C $(MLX_DIR) clean; fi
	@$(RM) -r $(OBJ_DIR)
	@echo "Cleaned object files."

fclean: clean
	@if [ -d "$(LIBFT_DIR)" ]; then make -s -C $(LIBFT_DIR) fclean; fi
	@$(RM) $(NAME)
	@echo "Removed binary: $(NAME)."

re: fclean all

distclean: fclean
	@$(RM) -r $(MLX_DIR)
	@echo "Removed MiniLibX directory."

.PHONY: all clean fclean re distclean