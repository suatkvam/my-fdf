NAME = fdf

INCLUDE_FLAGS = -I./error -I./utils -I./event -I./libft -I./parser -I./render

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

MLX_DIR = minilibx
MLX_URL = https://cdn.intra.42.fr/document/document/40303/minilibx-linux.tgz
MLX_TGZ = minilibx.tgz
MLX_EXTRACTED_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

# Allow skipping MiniLibX download/build for quick local tests:
# usage: make NOMLX=1
ifeq ($(NOMLX),1)
MLX_REQUIRED :=
MLX_FLAGS :=
else
MLX_REQUIRED := $(MLX_LIB)
endif

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

OBJ_DIR = obj
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra $(INCLUDE_FLAGS) -g

RM = rm -rf
SILENT = @

all: dirs $(NAME)

dirs:
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS) $(LIBFT_LIB) $(MLX_REQUIRED)
	@echo "Linking $(NAME)..."
	@$(CC) $(OBJS) $(LIBFT_FLAGS) $(MLX_FLAGS) -o $(NAME)
	@echo "\033[32mSuccessfully built $(NAME)!\033[0m"

$(OBJ_DIR)/%.o: %.c $(LIBFT_LIB) $(MLX_REQUIRED)
	@mkdir -p $(@D)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

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
	@$(RM) $(OBJ_DIR)
	@echo "Cleaned object files."

fclean: clean
	@if [ -d "$(LIBFT_DIR)" ]; then make -s -C $(LIBFT_DIR) fclean; fi
	@$(RM) $(NAME)
	@echo "Removed binary: $(NAME)."

re: fclean all

distclean: fclean
	@$(RM) $(MLX_DIR)
	@echo "Removed MiniLibX directory."

.PHONY: all dirs clean fclean re distclean