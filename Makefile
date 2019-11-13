# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: svan-der <svan-der@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/11/08 17:46:48 by svan-der       #+#    #+#                 #
#    Updated: 2019/11/13 14:49:44 by svan-der      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

HEADER = ./includes
SRC = $(addprefix srcs/,dispatch.c finish.c ft_vprintf.c ntoap.c parsing.c)
OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Werror -Wextra
DFLAGS = $(CFLAGS) -g

LIB = libft/libft.a
LIBB = libft.a
LIB_SRC = ./libft/srcs
LIB_BIN = -L ./libft -lft
LIBHEADER = ./libft/includes
HEADERS = -I$(HEADER) -I$(LIBHEADER)

all: $(NAME)

$(LIB): 
	make -C libft
	
$(NAME):$(LIB) $(OBJ)
	cp $(LIB) .
	mv $(LIBB) $(NAME)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)
	

$(OBJ): $(SRCDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

rebug: fclean debug

.PHONY: all so clean fclean re debug rebug libft
