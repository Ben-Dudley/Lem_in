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
		stack = score_stack_path(graph, info, queue, traces);
		score_ants(graph, info, stack);
	}
	free(queue);
	free(traces);
	score_ways(graph, info);
	if (info->max_flow == 0)
		error("It is impossible to translate ants\n", graph, info);
	return (1);
}
