/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 15:27:17 by bdudley           #+#    #+#             */
/*   Updated: 2019/09/05 17:30:03 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		init_graph(t_graph **graph, t_info *info, int i)
{
	while (i < info->count_max_node)
	{
		graph[0][i].name = NULL;
		graph[0][i].x = 0;
		graph[0][i].y = 0;
		graph[0][i].visited = 0;
		graph[0][i].weight = 2147483647;
		graph[0][i].link = NULL;
		i++;
	}
}

t_graph		*new_graph(t_graph *prev_graph, t_info *info)
{
	t_graph	*new_graph;
	int		i;

	i = 0;
	info->count_max_node *= 2;
	if (!(new_graph = (t_graph *)malloc(sizeof(*new_graph) *
			info->count_max_node)))
		error_message(&prev_graph, info, 0);
	while (i < info->count_node)
	{
		new_graph[i].name = prev_graph[i].name;
		new_graph[i].x = prev_graph[i].x;
		new_graph[i].y = prev_graph[i].y;
		new_graph[i].visited = prev_graph[i].visited;
		new_graph[i].link = prev_graph[i].link;
		i++;
	}
	init_graph(&new_graph, info, i);
	if (prev_graph != NULL)
	{
		free(prev_graph);
		prev_graph = NULL;
	}
	return (new_graph);
}

t_link		*new_link(t_graph **graph, t_info *info)
{
	t_link *new;

	if (!(new = (t_link *)malloc(sizeof(*new))))
		error_message(graph, info, 0);
	new->node = -1;
	new->status = 1;
	new->next = NULL;
	new->reverse = NULL;
	return (new);
}

void		add_link(t_link **link, t_link *new)
{
	new->next = *link;
	*link = new;
}

void		clear_graph(t_graph **graph, t_info *info, int flag)
{
	int				i;
	t_link			*temp;

	i = 0;
	while (i < info->count_node)
	{
		temp = graph[0][i].link;
		while (temp)
		{
			graph[0][temp->node].visited = 0;
			if (flag)
				if (!(temp->reverse->status == 0 && temp->status == 0))
					temp->status = 1;
			temp = temp->next;
		}
		++i;
	}
}
