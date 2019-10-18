/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 19:11:16 by hharrold          #+#    #+#             */
/*   Updated: 2019/09/20 20:50:10 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zconf.h>
#include "lem_in.h"

/*
** Solution determine which option this better,
** find stack max flow path and shortest path stack.
** It choose best variant and move ants.
** Here also is search paths max flow stack.
*/

void				score_stack_path(t_graph **graph, t_info *info,
										t_trace *trace)
{
	int				add_path;

	add_path = find_path(graph, info, trace);
	if (add_path == 0)
		error_message(graph, info, 69);
	while (add_path > 0)
	{
		info->max_flow += add_path;
		get_path_numbers(graph, info);
		if (score_stack(graph, info) == info->max_flow - 1 && info->max_flow > 1)
		{
			info->max_flow--;
			return ;
		}
		add_path = find_path(graph, info, trace);
	}
}

int					find_link_node(t_graph **graph, t_info *info, int node)
{
	t_link			*temp;

	temp = graph[0][info->ind_end].link;
	while (temp)
	{
		if (temp->node == node)
			return (1);
		temp = temp->next;
	}
	return (0);
}

void				create_del_trace(t_trace *temp,int configuration, t_graph **graph, t_info *info)
{
	if (configuration == 0)
	{
		free(temp->queue);
		free(temp->traces_0);
		free(temp->traces_1);
	}
	if (configuration == 1)
	{
		if (!(temp->queue = (int *)malloc(sizeof(int)
				* (info->count_node + 1))))
			error_message(graph, info, 0);
		if (!(temp->traces_0 = (int *)malloc(sizeof(int)
				* (info->count_node + 1))))
			error_message(graph, info, 0);
		if (!(temp->traces_1 = (int *)malloc(sizeof(int)
				* (info->count_node + 1))))
			error_message(graph, info, 0);
	}
}

int					solution(t_graph **graph, t_info *info)
{
	t_trace			trace;
	int				stack;

	create_del_trace(&trace, 1, graph, info);
	score_stack_path(graph, info, &trace);
	create_del_trace(&trace, 0, graph, info);
	if (info->max_flow > 0)
		score_ways(graph, info, info->max_flow);
	return (1);
}
