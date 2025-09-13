# Name of the final executable
NAME = fdf


#DIRECTORIES


# Directory for compiled object files (.o)
OBJ_DIR = obj

# Directories where source files (.c) are located for vpath
SRC_DIRS = srcs srcs/init srcs/parsing srcs/rendering srcs/events srcs/cleanup

# Paths to the external libraries
LIBFT_DIR = libft
MLX_DIR = minilibx


#SOURCE FILES 


# List all your .c source files here.
# vpath will find them in the directories specified in SRC_DIRS.
SRCS = main.c \
       # Add parsing files here (e.g., read_map.c)
       # Add rendering files here (e.g., draw.c)
       # etc.

# Automatically generate the object file paths from the source file list.
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))


#LIBRARIES


# Libft configuration
LIBFT_LIB = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

# MiniLibX configuration
MLX_URL = https://cdn.intra.42.fr/document/document/34669/minilibx-linux.tgz
MLX_TGZ = minilibx.tgz
MLX_EXTRACTED_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz


#COMPILER AND FLAGS

CC = cc
# Standard compilation flags
CFLAGS = -Wall -Wextra -Werror -g
# Paths for header files (-I)
INCLUDE_FLAGS = -I./includes -I$(LIBFT_DIR) -I$(MLX_DIR)
# Append include paths to CFLAGS
CFLAGS += $(INCLUDE_FLAGS)

RM = rm -f
SILENT = @


#RULES  


# Default rule: builds the entire project.
all: $(NAME)

# Rule to link the final executable.
# Depends on object files and library files.
$(NAME): $(OBJS) $(LIBFT_LIB) $(MLX_LIB)
	$(SILENT)echo "Linking $(NAME)..."
	$(SILENT)$(CC) $(OBJS) $(LIBFT_FLAGS) $(MLX_FLAGS) -o $(NAME)
	$(SILENT)echo "\033[32mSuccessfully built $(NAME)!\033[0m"

# Generic rule to compile .c files into .o files inside OBJ_DIR.
$(OBJ_DIR)/%.o: %.c
	$(SILENT)mkdir -p $(@D)
	$(SILENT)echo "Compiling $<..."
	$(SILENT)$(CC) $(CFLAGS) -c $< -o $@

# Tell 'make' where to find the source files listed in SRCS.
vpath %.c $(SRC_DIRS)

# Rule to build the Libft library.
$(LIBFT_LIB):
	$(SILENT)echo "Building Libft..."
	$(SILENT)make -s -C $(LIBFT_DIR)

# Rule to download, set up, and build the MiniLibX library if it doesn't exist.
$(MLX_LIB):
	$(SILENT)if [ ! -d "$(MLX_DIR)" ]; then \
		echo "MiniLibX not found. Downloading..."; \
		wget -q -O $(MLX_TGZ) $(MLX_URL); \
		tar -xzf $(MLX_TGZ); \
		mv $(MLX_EXTRACTED_DIR) $(MLX_DIR); \
		rm -f $(MLX_TGZ); \
		echo "MiniLibX setup complete."; \
	fi
	$(SILENT)echo "Building MiniLibX..."
	$(SILENT)make -s -C $(MLX_DIR)


#CLEANING RULES

# Removes object files.
clean:
	$(SILENT)if [ -d "$(LIBFT_DIR)" ]; then make -s -C $(LIBFT_DIR) clean; fi
	$(SILENT)if [ -d "$(MLX_DIR)" ]; then make -s -C $(MLX_DIR) clean; fi
	$(SILENT)$(RM) -r $(OBJ_DIR)
	$(SILENT)echo "Cleaned object files."

# Removes object files and the final executable.
fclean: clean
	$(SILENT)if [ -d "$(LIBFT_DIR)" ]; then make -s -C $(LIBFT_DIR) fclean; fi
	$(SILENT)$(RM) $(NAME)
	$(SILENT)echo "Removed binary: $(NAME)."

# Cleans and rebuilds the project.
re: fclean all

# Cleans everything, including downloaded libraries (dist-clean).
distclean: fclean
	$(SILENT)$(RM) -r $(MLX_DIR)
	$(SILENT)echo "Removed MiniLibX directory."

# Declare rules that are not actual files.
.PHONY: all clean fclean re distclean