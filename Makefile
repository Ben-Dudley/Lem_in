# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bdudley <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/17 23:17:28 by bdudley           #+#    #+#              #
#    Updated: 2019/09/20 12:20:12 by bdudley          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
FLAGS = -Wall -Wextra -Werror
INC = ./include
INC_2 = ./libft
SRCS = ./source/main.c ./source/graph_operations.c \
		./source/get_rooms_links.c ./source/put_number.c \
		./source/get_rooms_ants.c ./source/print_graph.c ./source/solution.c \
		./source/search_path.c ./source/path_operations.c ./source/score_ants.c \
		./source/find_path.c ./source/error_message.c ./source/move_ant.c \
		./source/pars_flag.c ./source/merge_sort.c ./source/stack_operations.c \
		./source/print_move.c ./source/writer_base.c \
		./source/for_flag_v.c ./source/fordfalkerson.c \
		./source/restoration_path.c

OBJS = $(SRCS:.c=.o)
LIB = ./libft/libft.a

all: $(NAME)

$(NAME): $(OBJS)
	@make -C ./libft
	@gcc $(FLAGS) $(OBJS) $(OBJS_P) $(LIB) -o $(NAME)

%.o: %.c
	@gcc $(FLAGS) -c $< -o $@ -I$(INC) -I$(INC_2)

clean:
	@make -C ./libft clean
	@rm -f $(OBJS)

fclean: clean
	@make -C ./libft fclean
	@rm -f $(NAME)

re: fclean all
