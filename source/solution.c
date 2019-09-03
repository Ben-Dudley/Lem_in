/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 19:11:16 by hharrold          #+#    #+#             */
/*   Updated: 2019/08/31 19:11:53 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				score_stack_path(t_graph **graph, t_info *info,
										int *queue, int *traces)
{
	int	count;
	int add_path;

	add_path = find_path(graph, info, queue, traces);
	while (add_path > 0)
	{
		count += add_path;
		add_path = find_path(graph, info, queue, traces);
	}
	clear_graph(graph, info);
	return (count);
}

int				find_link_node(t_graph **graph, t_info *info, int node)
{
	t_link  *temp;

	temp = graph[0][info->ind_end].link;
	while (temp)
	{
		if (temp->node == node)
			return (1);
		temp = temp->next;
	}
	return (0);
}

void				get_path_numbers(t_graph **graph, t_info *info)
{
	t_link        *temp;
	t_path        *path;

	int            i;

	i = 1;


	while (i <= info->max_flow)
	{
		temp = graph[0][info->ind_start].link;

		path = new_path(graph, info);
		add_path(&info->path, path);
		while (temp)
		{
			if ( graph[0][temp->node].visited == i)
			{
				add_node(&path->node, new_node(graph, info, temp->node));
				temp = graph[0][temp->node].link;
			}
			else
				temp = temp->next;
		}
		add_node(&path->node, new_node(graph, info, info->ind_end));
		++i;
	}
}

int				stack_max_flow(t_graph **graph, t_info *info, int index, int flow)
{
	t_link	*temp;

	while (flow <= info->max_flow)
	{
		temp = graph[0][index].link;
		while (temp)
		{
			if (find_link_node(graph, info, temp->node))
			{
				if (stack_max_flow(graph, info, info->ind_start, flow + 1))
					return (1);
			}
			else if (graph[0][temp->node].visited == 0)
			{
				graph[0][temp->node].visited = flow;
				if (stack_max_flow(graph, info, temp->node, flow) == 0)
					graph[0][temp->node].visited = 0;
			}
			temp = temp->next;
		}
		return (0);
	}
	return (1);
}

int				solution(t_graph **graph, t_info *info)
{
	int *queue;
	int *traces;
	int stack;

	if (!(queue = (int *)malloc(sizeof(int) * (info->count_node + 1))))
		error("Memory allocation error\n", graph, info);
	if (!(traces = (int *)malloc(sizeof(int) * (info->count_node + 1))))
		error("Memory allocation error\n", graph, info);
	stack = score_stack_path(graph, info, queue, traces);
	info->count_ants *= -1;
	info->max_flow = score_stack_path(graph, info, queue, traces);
	info->count_ants *= -1;
	printf("ЪУЪ %d\n", info->count_ants);
	if (stack < info->max_flow)
	{
		stack_max_flow(graph, info, info->ind_start, 1);
		//stack = score_stack_path(graph, info, queue, traces);
		score_ants(graph, info, stack);
	}
	free(queue);
	free(traces);
	score_ways(graph, info);
	if (info->max_flow == 0)
		error("It is impossible to translate ants\n", graph, info);
	return (1);
}
