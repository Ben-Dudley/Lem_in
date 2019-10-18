/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 16:30:07 by bdudley           #+#    #+#             */
/*   Updated: 2019/09/20 16:35:51 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <limits.h>
# include <stdio.h>
# define SIZE 2048
# define BUFF 1024

typedef struct			s_node
{
	int					node;
	int					ant;
	struct s_node		*next;
}						t_node;

typedef struct			s_path
{
	int					length;
	int					stack; //zachem
	t_node				*node;
	struct s_path		*next;
}						t_path;

typedef struct			s_stack
{
	int					stack;
	t_path				*path;
	struct s_stack		*next;
}						t_stack;

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
	int					weight;
	int					visited;
	t_link				*link;

}						t_graph;

typedef struct			s_trace
{
	int					*queue;
	int					*traces_0;
	int					*traces_1;
}						t_trace;

typedef struct			s_info
{
	int					flag_score;
	int					flag_score_in_file : 1;
	int					flag_visual : 1;
	int					flag_colour : 1;
	int					flag_way : 1;
	int					flag_all_way : 1;
	int					flag_print_graph;
	int					count_ants;
	int					count_node;
	int					count_max_node;
	int					ind_start;
	int					ind_end;
	int					max_flow;
	t_stack				*stack;
	int					len_buf;
	char				buf[BUFF];
	char				*basic_information;
	int					buf_size;
}						t_info;

/*
** delete help function
*/
int						search_stack_path(t_graph **graph, t_info *info,
							int *queue, int *traces);
int						error_message(t_graph **graph, t_info *info,
							int code_error);
void					reverse_path(t_graph **graph, t_info *info);
void					print_queue(t_graph **graph, int *queue, int count);
void					print_ways(t_info *info, int *ways, int count);
void					ft_print_pyti(t_graph **graph, t_info *info);
void					print_massiv(t_graph **graph, t_info *info);

void					print_max(t_graph **graph, t_info *info);
void					for_fix_stack(t_graph **graph, t_info *info);
void					print_stack(t_graph **graph, t_info *info);
void					print_links(t_graph **graph, t_info *info);
/*
** print graph
*/
void					reverse_list(t_graph **graph, t_info *info);
void					reverse_node(t_path **path);
void					print_graph(t_graph **graph, t_info *info); //rename function
void					print_move(t_graph **graph, t_info *info,
							int count, int count_ways);
void					print_buf(t_info *info, char *str);
int						send_to_print_steps(t_node *temp_node, int i,
											t_info *info, t_graph **graph);
void					buf_init(t_info *info);
void					writer_base(t_info *info, char *line);
void					for_flag_v(t_graph **graph, t_info *info);
/*
** find path for ants
*/
int						solution(t_graph **graph, t_info *info);
int						score_stack(t_graph **graph, t_info *info);
void					steps_ants(t_graph **graph, t_info *info,
							int *ways, int count_ways);
void					score_ways(t_graph **graph, t_info *info,
										int count_ways);
int						min_score_ants(t_info *info, int count,
										int count_ways);
/*
** find max flow and stack with shortest path
*/
void					score_stack_path(t_graph **graph, t_info *info,
															t_trace *trace);
int						find_path(t_graph **graph, t_info *info,
															t_trace *trace);
void					save_path(t_graph **graph, t_info *info, t_trace *trace,
																		int i);
void					restoration_path(t_graph **graph, t_info *info,
															t_trace *trace);
void					clear_graph(t_graph **graph, t_info *info);
void					del_flow(t_graph **graph, t_info *info, int count);
void					get_path_numbers(t_graph **graph, t_info *info);
/*
** parse input data
*/
void					init(t_graph **graph, t_info *info);
void					error(char *str, t_graph **graph, t_info *info);
int						put_number(char *str, t_graph **graph, t_info *info);
int						get_ants(t_graph **graph, t_info *info);
void					get_rooms_links(t_graph **graph, t_info *info);
void					get_room(t_graph **graph, t_info *info, int *flag,
							char *line);
int						help_rooms(t_graph **graph, t_info *info, int flag,
							char *line); //rename this function

int						flag_checking(int ac, char **av, t_graph **graph,
												t_info *info);
void					print_flags(t_info *info);
/*
** Create and init structure
*/
t_link					*new_link(t_graph **graph, t_info *info);
void					add_link(t_link **link, t_link *new);
void					free_link(t_link **link);

t_graph					*new_graph(t_graph *prev_graph, t_info *info);
size_t					*new_links(t_graph *graph, t_info *info);

t_path					*new_path(t_graph **graph, t_info *info);
void					add_path(t_path **path, t_path *new);

t_node					*new_node(t_graph **graph, t_info *info, int node);
void					add_node(t_node **node, t_node *new);

t_stack					*new_stack(t_graph **graph, t_info *info,
										int stack, t_path *path);
void					add_stack(t_stack **stack, t_stack *new);
void					in_stack_add(t_graph **graph, t_info *info,
										int stack, t_path *path);
/*
** Sorted
*/
void					merge_sort(t_graph **graph, t_info *info);
void					for_fix_stack(t_graph **graph, t_info *info);
/*
** ford_fa
*/
int				check_visited(t_graph **graph, t_link *ptr,
								 t_trace *trace, int i);
int				clear_end_link_weight(t_graph **graph,
													t_info *info, t_trace *trace);
int				visited_on_node(t_graph **graph, t_link *ptr,
								   t_trace *trace, int i);
int				not_node(t_info *info, t_link *ptr, t_trace *trace, int i);
int				algorithm(t_graph **graph, t_link *ptr,
							 t_trace *trace, int *ij);
int		find_index(t_info *info, t_trace *trace, int node);
int		init_mass(t_info *info, t_trace *trace);
void			free_graph(t_graph **graph, t_info *info);
void			free_path(t_stack *stack);
#endif
