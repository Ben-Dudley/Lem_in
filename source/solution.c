/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharrold <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 19:11:16 by hharrold          #+#    #+#             */
/*   Updated: 2019/08/27 19:11:18 by hharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zconf.h>
#include "lem_in.h"

void			print(t_graph **graph, t_info *info, int i)
{
	t_link		*temp;

	temp = graph[0][i].link;
	while (temp)
	{
		printf("%s-%s i = %d; temp->node = %d;\n", graph[0][i].name, graph[0][temp->node].name, i, temp->node);

		temp = temp->next;
	}
	printf("\n\n\n");
//	temp = graph[0][i].link;
//	while (temp)
//	{
//		printf("!!!!!%d\n", temp->node);
//		temp = temp->next;
//	}
}

void				print_queue(int *queue, int count)
{
	int i;

	i = 0;
	printf("%d", queue[i++]);
	while (i <= count)
		printf(" %d", queue[i++]);
	printf("\n");
}

void				restoration_path(t_graph **graph, t_info *info, int *traces)
{
	int 		i;
	t_link		*temp;

	i = info->ind_end;
	while (i != info->ind_start)
	{
		print(graph, info, i);
		temp = 	graph[0][traces[i]].link;
		while (temp)
		{
			if (temp->node == i)
			{
				temp->status = 0;
				break ;
			}
			temp = temp->next;
		}
		i = traces[i];
	}
}

int					find_path(t_graph **graph, t_info *info, int *queue, int *traces)
{
	int			i;
	int 		j;
	t_link		*ptr;

	i = 0;
	queue[i] = info->ind_start;
//	print_queue(queue, i);
	//printf("after cycle\n");
	while (queue[i] != -1)
	{

		//printf("queue[i] = %d\n", queue[i]);
		ptr = graph[0][queue[i]].link;
		while (ptr)
		{
			if (ptr->status != 0)
			{
				//print(graph, info, i);
				j = 0;
				while (j < i)
				{
					if (queue[j] == ptr->node)
						break;
					j++;
				}
				if (j == i)
				{
					j = i;
					j++;
					queue[j] = ptr->node;
					traces[ptr->node] = queue[i];
					if (ptr->node == info->ind_end)
					{
						restoration_path(graph, info, traces);
						return (1);
					}
				}
			}
			ptr = ptr->next;
		}
	//	print_queue(queue, i);
		i++;
	}
	return (0);
}

int					solution(t_graph **graph, t_info *info)
{
	int max_flow;
	int add_path;
	int *queue;
	int *traces;
	int i;

	i = 0;
	max_flow = 0;
	if (!(queue = (int *)malloc(sizeof(int) * (info->count_node + 1))))
		error("Memory allocation error\n", graph, info);
	if (!(traces = (int *)malloc(sizeof(int) * (info->count_node + 1))))
		error("Memory allocation error\n", graph, info);
	while (i <= info->count_node)
		queue[i++] = -1;
	i = 0;
	while (i <= info->count_node)
		traces[i++] = -1;
	//printf("I exist!!\n");
	add_path = find_path(graph, info, queue, traces);
	while (add_path > 0)
	{
		max_flow += add_path;
		add_path = find_path(graph, info, queue, traces);
	}
	free(queue);
	printf("max flow %d\n", max_flow);
	if (max_flow == 0)
		error("It is impossible to translate ants\n", graph, info);
	return (1);
}
