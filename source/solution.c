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

#include "lem_in.h"

void			print(t_graph **graph, t_info *info, int i)
{
	t_link		*temp;

	temp = graph[0][i].link;
	while (temp)
	{
		printf("%s-%s\n", graph[0][i].name, graph[0][temp->node].name);
		temp = temp->next;
	}
	temp = graph[0][i].link;
	while (temp)
	{
		printf("!!!!!%d\n", temp->node);
		temp = temp->next;
	}
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

int					find_path(t_graph **graph, t_info *info, int *queue)
{
	int			i;
	int 		j;
	t_link		*ptr;

	i = 0;
	queue[i] = info->ind_start;
	print_queue(queue, i);
	printf("after cycle\n");
	while (queue[i] != -1)
	{
		printf("queue[i] = %d\n", queue[i]);
		ptr = graph[0][queue[i]].link;
		while (ptr)
		{
			print(graph, info, i);
			j = 0;
			if (ptr->node == info->ind_end)
			{
				//save path and return
			}
			while (j < i)
			{
				if (queue[j] == ptr->node)
					break ;
				j++;
			}
			if (j == i)
			{
				j = i;
				j++;
				queue[j] = ptr->node;
			}
			ptr = ptr->next;
		}
		print_queue(queue, i);
		i++;
	}
	return (0);
}

int					solution(t_graph **graph, t_info *info)
{
	int max_flow;
	int add_path;
	int *queue;
	int *link;
	int i;

	i = 0;
	max_flow = 0;
	if (!(queue = (int *)malloc(sizeof(int) * (info->count_node + 1))))
		error("Memory allocation error\n", graph, info);
	while (i <= info->count_node)
		queue[i++] = -1;
	print_queue(queue, info->count_node);
	printf("I exist!!\n");
	add_path = find_path(graph, info, queue);
	while (add_path > 0)
	{
		max_flow += add_path;
		add_path = find_path(graph, info, queue);
		//clear queue
	}
	free(queue);
	if (max_flow == 0)
		error("It is impossible to translate ants\n", graph, info);
	return (1);
}
