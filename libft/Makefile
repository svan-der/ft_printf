# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: svan-der <svan-der@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/02/11 15:22:00 by svan-der       #+#    #+#                 #
#    Updated: 2019/11/12 18:32:31 by svan-der      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra
HEADER = includes/
SRCDIR = srcs/
SRC = $(addprefix $(SRCDIR),ft_memchr.c ft_putnbr_fd.c ft_striter.c ft_strnew.c ft_atoi.c\
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
	
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):$(OBJ)
	ar rcs $(NAME) $(OBJ)
$(OBJ): $(SRCDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) -I$(HEADER) -c $< -o $@
	
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re