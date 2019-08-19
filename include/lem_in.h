/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 16:30:07 by bdudley           #+#    #+#             */
/*   Updated: 2019/08/19 21:14:04 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

#include "libft.h"
#include <limits.h>
#include <stdio.h>

typedef struct	s_link
{
	char				*node_1;
    char				*node_2;
    struct s_link		*next;
}						t_link;

typedef struct	s_graph
{
	char			*name;
	t_link			**link;
	struct s_graph	*next;
}				t_graph;

typedef struct	s_info
{
	int			count_ants;
}				t_info;


t_link	*new_link(char *node1, char *node2);
void	add_link(t_link **link, t_link *new);
void 	free_link(t_link **link);

t_graph	*new_graph(char *name, t_link **link);
void add_graph(t_graph **graph, t_graph *new);
void	free_graph(t_graph **graph);

void	init(t_graph **graph, t_info **info);
void	error(char *str, t_graph **graph, t_info **info);

void	get_ants(t_graph **graph, t_info **info);
void	get_rooms_links(t_graph **graph, t_info **info);

#endif