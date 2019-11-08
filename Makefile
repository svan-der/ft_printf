# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: svan-der <svan-der@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/11/08 17:46:48 by svan-der       #+#    #+#                 #
#    Updated: 2019/11/08 18:43:02 by svan-der      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra
DFLAGS = $(CFLAGS) -g

OBJ = $(SRC:%.c=%.o)
LIB = libft/libft.a
DEBUG = $(LIB)

INCDIRS = $(dir includes, libft/includes)
INCS = -I$(INCDIRS)

SRCDIR = srcs
SRCS = libft/srcs/
SRC = $($(SRCDIR), $(SRCS))

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)
	
%.o: %.c
    # $(CC) $(CFLAGS) -o $@ -c $<
	@echo "RED[recompiling] $< $@"
	@(CC) $(CFLAGS) $(INCS) $(SRCFILES)
debug: $(DEBUG)

$(DEBUG):
	ar rcs $(DEBUG) $(OBJ)
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME) $(DEBUG)
re: fclean all

rebug: fclean debug

.PHONY: all so clean fclean re debug rebug