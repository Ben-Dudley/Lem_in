/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 16:30:07 by bdudley           #+#    #+#             */
/*   Updated: 2019/08/21 20:00:43 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <limits.h>
# include <stdio.h>
# define SIZE 16
typedef struct 			s_node
{
	int 				node;
	struct s_node		*next;
}						t_node;

typedef struct 			s_path
{
	int 				length;
	int 				stack;
	t_node				*node;
	struct s_path		*next;
}						t_path;

typedef struct			s_link
{
	int					status;
	int					node;
	struct s_link		*reverse;
	struct s_link		*next;
//	int 				score;
}						t_link;
//while (t_list->next)
////	score++; ft_strjoin(*int reversa* int)

typedef struct			s_graph
{
	char				*name;
	int					x;
	int					y;
	int					visited;
	t_link				*link;

}						t_graph;

typedef struct			s_info
{
	int					count_ants;
	int					count_node;
	int					count_max_node;
	int					ind_start;
	int					ind_end;
}						t_info;

t_link					*new_link(t_graph **graph, t_info *info);
void					add_link(t_link **link, t_link *new);
void					free_link(t_link **link);

t_graph					*new_graph(t_graph *prev_graph, t_info *info);
size_t					*new_links(t_graph *graph, t_info *info);

void					init(t_graph **graph, t_info *info);
void					error(char *str, t_graph **graph, t_info *info);
int						put_number(char *str, t_graph **graph, t_info *info);

void					get_ants(t_graph **graph, t_info *info);
void					get_rooms_links(t_graph **graph, t_info *info);
void					get_room(t_graph **graph, t_info *info, int *flag,
																char *line);
void					ft_print_massiv(t_graph **graph, t_info *info);
int						ft_help_rooms(t_graph **graph, t_info *info, int flag,
																char *line);
int						solution(t_graph **graph, t_info *info);
#endif
