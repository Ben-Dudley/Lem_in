/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 16:30:07 by bdudley           #+#    #+#             */
/*   Updated: 2019/08/31 19:10:12 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Create and init structure */
#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <limits.h>
# include <stdio.h>
# define SIZE 5001

typedef struct			s_node
{
	int					node;
	int					ant;
	struct s_node		*next;
}						t_node;

typedef struct			s_path
{
	int					length;
	int					stack;
	t_node				*node;
	struct s_path		*next;
}						t_path;

typedef struct			s_link
{
	int					status;
	int					node;
	struct s_link		*reverse;
	struct s_link		*next;
}						t_link;

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
	int					max_flow;
	t_path				*path;
}						t_info;

void					init(t_graph **graph, t_info *info);
void					error(char *str, t_graph **graph, t_info *info);
int						put_number(char *str, t_graph **graph, t_info *info);

void					get_ants(t_graph **graph, t_info *info);
void					get_rooms_links(t_graph **graph, t_info *info);
void					get_room(t_graph **graph, t_info *info, int *flag,
																char *line);
void					ft_print_massiv(t_graph **graph, t_info *info);
int						help_rooms(t_graph **graph, t_info *info, int flag,
																char *line);
int						solution(t_graph **graph, t_info *info);
int						find_path(t_graph **graph, t_info *info,
							int *queue, int *traces);
void					save_path(t_graph **graph, t_info *info, int *traces);
int						search_stack_path(t_graph **graph, t_info *info,
							int *queue, int *traces);
void					ft_print_pyti(t_graph **graph, t_info *info);
void					clear_graph(t_graph **graph, t_info *info);
void					print_massiv(t_graph **graph, t_info *info);
void					print_queue(t_graph **graph, int *queue, int count);
void					print_ways(t_info *info, int *ways, int count);
void					score_ants(t_graph **graph, t_info *info, int count);
void					score_ways(t_graph **graph, t_info *info);
void					reverse_list(t_graph **graph, t_info *info);
void					steps_ants(t_graph **graph, t_info *info,
							int *ways, int count_ways);
void					reverse_path(t_graph **graph, t_info *info);
void					restoration_path(t_graph **graph, t_info *info,
							int *traces);
int						score_stack_path(t_graph **graph, t_info *info,
							int *queue, int *traces);
void					reverse_node(t_path **path);
int                error_message(t_graph **graph, t_info *info, int code_error);


t_link					*new_link(t_graph **graph, t_info *info);
void					add_link(t_link **link, t_link *new);
void					free_link(t_link **link);

t_graph					*new_graph(t_graph *prev_graph, t_info *info);
size_t					*new_links(t_graph *graph, t_info *info);

t_path					*new_path(t_graph **graph, t_info *info);
void					add_path(t_path **path, t_path *new);

t_node					*new_node(t_graph **graph, t_info *info, int node);
void					add_node(t_node **node, t_node *new);

#endif
