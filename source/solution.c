/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 19:11:16 by hharrold          #+#    #+#             */
/*   Updated: 2019/08/30 20:36:40 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
}

void				print_queue(t_graph **graph, int *queue, int count)
{
	int i;

	i = 0;
	while (i <= count)
	{
		if (queue[i] == -1)
			printf(" %d ", queue[i]);
		else
			printf(" %d(%s) ", queue[i], graph[0][queue[i]].name);
		++i;
	}
	printf("\n");
}

void				restoration_path(t_graph **graph, t_info *info, int *traces)
{
	int 		i;
	t_link		*temp;

	i = info->ind_end;
	while (i != info->ind_start)
	{
		//print(graph, info, i);
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
	//print_massiv(graph, info);
}

int					find_path(t_graph **graph, t_info *info, int *queue, int *traces, int GG)
{
	int			i;
	int 		j;
	t_link		*ptr;

	i = 0;
	while (i <= info->count_node)
		queue[i++] = -1;
	i = 0;
	while (i <= info->count_node)
		traces[i++] = -1;
	i = 0;
	queue[i] = info->ind_start;
	//printf("TYT\n");
	while (queue[i] != -1)
	{
		printf("Print queue before cycle\n");
		print_queue(graph, queue, i);
		printf("Print traces before cycle\n");
		print_queue(graph, traces, info->count_node);
		//printf("Zenya2\n");
		ptr = graph[0][queue[i]].link;
		while (ptr)
		{
			//printf("PYPA\n");
			if (ptr->status != 0 && graph[0][ptr->node].visited == 0)//&& (ptr-> node == info->ind_start || graph[0][ptr->node].visited == 0))
			{
				j = 0;
				while (j <= info->count_node)
				{
					if (queue[j] == ptr->node)
						break;
					j++;
				//	printf("a\n");
				}
				if (j == info->count_node + 1)
				{
					//printf("TYT1\n");
					j = i;
					while (queue[j] != -1)
						++j;
					queue[j] = ptr->node;
					traces[ptr->node] = queue[i];
					if (ptr->node == info->ind_end)
					{
						//printf("LYPA\n");
						if (GG)//(graph[0][info->ind_start].visited)
							save_path(graph, info, traces);
						else
							restoration_path(graph, info, traces);
						return (1);
					}
				}
			}
			//printf("KEK\n");
			ptr = ptr->next;
		}
		i++;
	}
	return (0);
}

int					solution(t_graph **graph, t_info *info)
{
	int add_path;
	int *queue;
	int *traces;
	int i;

	i = 0;
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
	i = search_stack_path(graph, info, queue, traces);
	add_path = find_path(graph, info, queue, traces, 0);
	//printf("i = %d add = %d\n", i , add_path);
	while (add_path > 0)
	{

		info->max_flow += add_path;
		add_path = find_path(graph, info, queue, traces, 0);
	}
	printf("max flow %d and count %d\n", info->max_flow, i);
	clear_graph(graph, info);
	if (i < info->max_flow)
		i = search_stack_path(graph, info, queue, traces);
	free(queue);
	ft_print_pyti(graph, info);
	printf("max flow %d and count %d\n", info->max_flow, i);
	if (info->max_flow == 0)
		error("It is impossible to translate ants\n", graph, info);
	return (1);
}
