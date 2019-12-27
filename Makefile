# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: svan-der <svan-der@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/11/08 17:46:48 by svan-der       #+#    #+#                 #
#    Updated: 2019/12/27 16:06:04 by svan-der      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

HEADER = ./includes
SRC = $(addprefix srcs/,ft_printf.c dispatch.c finish.c ft_vprintf.c ntoap.c\
	parsing.c ftoa.c ft_ldtoap.c ft_ftoap.c utils.c padding.c getarg.c frac.c)\

SRCDIR = srcs
OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Werror -Wextra
DFLAGS = $(CFLAGS) -g

LIB = libft/libft.a
LIB_SRC = $(addprefix $(LIB_DIR),ft_memchr.c ft_putnbr_fd.c ft_striter.c\
	ft_strnew.c ft_atoi.c ft_abs.c ft_pow.c\
	ft_memcmp.c ft_putstr.c ft_itoa.c ft_gridset.c\
	ft_bzero.c ft_memcpy.c ft_putstr_fd.c ft_strjoin.c ft_strrchr.c\
	ft_isalnum.c ft_memdel.c ft_strcat.c ft_strlcat.c ft_strstr.c\
	ft_memmove.c ft_strchr.c ft_strlen.c ft_strsub.c\
	ft_isascii.c ft_memset.c ft_tolower.c\
	ft_isdigit.c ft_strcmp.c ft_min_max.c ft_numlen.c\
	ft_strcpy.c ft_strncat.c ft_strsplit.c\
	ft_strdel.c ft_memalloc.c \
	ft_memccpy.c ft_putnbr.c \
	ft_strtrim.c ft_strarrdel.c ft_find_word.c ft_lstmap.c\
	ft_count_words.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c\
	ft_lstadd.c ft_lstiter.c ft_memdup.c)\

LIB_OBJ = $(LIB_SRC:.c=.o)
LIBB = libft.a
LIB_DIR = ./libft/srcs/
LIB_BIN = -L./libft -lft

LIBHEADER = ./libft/includes
HEADERS = -I$(HEADER) -I$(LIBHEADER)

all: $(NAME) $(LIB_OBJ)

$(NAME): $(OBJ) $(LIB_OBJ)
	ar rc $(NAME) $(OBJ) $(LIB_OBJ)
	ranlib $(NAME)

$(OBJ): $(SRCDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(LIB_OBJ): $(LIB_DIR)%.o: $(LIB_DIR)%.c
	$(CC) $(CFLAGS) -I$(LIBHEADER) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -f $(LIB_OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIB)

re: fclean all

rebug: fclean debug

.PHONY: all so clean fclean re debug rebug libft
