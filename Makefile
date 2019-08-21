# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bdudley <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/17 23:17:28 by bdudley           #+#    #+#              #
#    Updated: 2019/08/21 18:14:03 by bdudley          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem_in
#FLAGS = -Wall -Wextra -Werror
INC = ./include
INC_2 = ./libft
SRCS = ./source/main.c ./source/graph_operations.c ./source/get_ants_rooms_links.c
OBJS = $(SRCS:.c=.o)
LIB = ./libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(OBJS_P)
	make -C ./libft
	gcc $(FLAGS) $(OBJS) $(OBJS_P) $(LIB) -o $(NAME)

%.o: %.c
	gcc $(FLAGS) -c $< -o $@ -I$(INC) -I$(INC_2)

clean:
	make -C ./libft clean
	rm -f $(OBJS)

fclean: clean
	make -C ./libft fclean
	rm -f $(NAME)

re: fclean all
