# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bdudley <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/26 17:59:10 by bdudley           #+#    #+#              #
#    Updated: 2018/12/15 01:38:43 by bdudley          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

I = gcc -Wall -Wextra -Werror -c

OPART1 = ft_memset.o ft_bzero.o ft_memcpy.o ft_memccpy.o ft_memmove.o ft_memchr.o ft_memcmp.o ft_strlen.o ft_strdup.o ft_strcpy.o ft_strncpy.o ft_strcat.o ft_strncat.o ft_strlcat.o ft_strchr.o ft_strrchr.o ft_strstr.o ft_strnstr.o ft_strcmp.o ft_strncmp.o ft_atoi.o ft_isalpha.o ft_isdigit.o ft_isalnum.o ft_isascii.o ft_isprint.o ft_toupper.o ft_tolower.o

OPART2 = ft_memalloc.o ft_memdel.o ft_strnew.o ft_strdel.o ft_strclr.o ft_striter.o ft_striteri.o ft_strmap.o ft_strmapi.o ft_strequ.o ft_strnequ.o ft_strsub.o ft_strjoin.o ft_strtrim.o ft_strsplit.o ft_itoa.o ft_putchar.o ft_putstr.o ft_putendl.o ft_putnbr.o ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o

OPART3 = ft_lstnew.o ft_lstdelone.o ft_lstdel.o ft_lstadd.o ft_lstiter.o ft_lstmap.o ft_lstadd_back.o quicksort.o ft_find_elem.o ft_lstadd_elem.o ft_lstdelone_elem.o get_next_line.o

CPART1 = $(OPART1:.o=.c)
CPART2 = $(OPART2:.o=.c)
CPART3 = $(OPART3:.o=.c)

all: $(NAME)

$(OPART1) = %.o : libft.h
$(OPART2) = %.o : libft.h
$(OPART3) = %.o : libft.h

$(NAME): $(OPART1) $(OPART2) $(OPART3)
	$(I) $(CPART1) $(CPART2) $(CPART3)
	ar rc $(NAME) $(OPART1) $(OPART2) $(OPART3)

clean:
	rm -f $(OPART1) $(OPART2) $(OPART3)

fclean: clean
	rm -f $(NAME)

re: fclean all
