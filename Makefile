# Name of the final executable
NAME = fdf

# Directories

# Directory for compiled object files (.o)
OBJ_DIR = obj

# Paths to the external libraries
LIBFT_DIR = libft
MLX_DIR = minilibx

# source files

ERROR_SRC=
EVENT_SRC=
PARSER_SRC= 
RENDER_SRC=
UTILS_SRC=

SRCS = $(addprefix error/, $(ERROR_SRC)) \
	 $(addprefix utils/, $(UTILS_SRC)) \
	 $(addprefix parser/, $(PARSER_SRC)) \
	 $(addprefix render/, $(RENDER_SRC)) \
	 $(addprefix event/, $(EVENT_SRC)) \
	 main.c

# Automatically generate the object file paths.
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# libraries

LIBFT_LIB = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

MLX_URL = https://cdn.intra.42.fr/document/document/40303/minilibx-linux.tgz
MLX_TGZ = minilibx.tgz
MLX_EXTRACTED_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

# compiler and flags

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDE_FLAGS = -I./includes -I./get-next-line -I./libft -I./ft_printf -I./minilibx -I./parser
CFLAGS += -g
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


$(LIBFT_LIB):
	@echo "Building Libft..."
	@make -s -C $(LIBFT_DIR)

$(MLX_LIB):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "MiniLibX not found. Downloading..."; \
		# Try the default URL first, if it fails prompt the user for a new one \
		MLX_DL_URL="$(MLX_URL)"; \
		while true; do \
			echo "Attempting to download from $$MLX_DL_URL"; \
			if wget -q -O $(MLX_TGZ) "$$MLX_DL_URL"; then \
				echo "Download succeeded."; \
				break; \
			fi; \
			echo "Download failed from: $$MLX_DL_URL"; \
			printf "Enter a new URL for MiniLibX (or press Enter to abort): "; \
			read NEW_URL || { echo "No input detected. Aborting."; exit 1; }; \
			if [ -z "$$NEW_URL" ]; then echo "Aborted by user."; exit 1; fi; \
			MLX_DL_URL="$$NEW_URL"; \
		done; \
		# Extract and move; \
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