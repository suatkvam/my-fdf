NAME = libftprintf.a

SRC = ft_pointer_adress.c ft_printf.c ft_putchar.c \
	  ft_puthex.c ft_putnbr.c ft_putstr.c ft_putnbr_unsigned.c

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.phony: all clean fclean re
