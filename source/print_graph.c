/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 17:24:18 by hharrold          #+#    #+#             */
/*   Updated: 2019/09/04 18:15:27 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				print_move(t_graph **graph, t_info *info, int count)
{
	t_path		*temp;
	t_node		*temp_node;
	int			i;
	int			counter;

	i = 0;
	while (i < count)
	{
		counter = i;
		temp = info->path;
		while (temp)
		{
			temp_node = temp->node;
			while (temp_node)
			{
				if (i == temp_node->ant)
				{
					if (temp_node->ant)
					printf("L%d-%s ", temp_node->ant, graph[0][temp_node->node].name); //space
					++i;
				}
				temp_node = temp_node->next;
			}
			temp = temp->next;
		}
		if (counter == i)
			i++;
	}
	printf("\n");
}

void				steps_ants(t_graph **graph, t_info *info, int *ways, int count_ways)
{
	t_node		*ptr_node;
	t_path		*ptr_path;
	int			j;
	int			i;
	int			score_ants;

	j = 1;
	score_ants = 0;
	while (score_ants < info->count_ants)
	{
		i = 0;
		ptr_path = info->path;
		while (ptr_path)
		{
			ptr_node = ptr_path->node;
			if (ptr_node->node && !ptr_node->next->node)
				score_ants += 1;
			while (ptr_node->next->node != info->ind_start)
			{
				ptr_node->ant = ptr_node->next->ant;
				if (ptr_node->node == info->ind_end && ptr_node->next->ant != 0)
					score_ants += 1;
				ptr_node = ptr_node->next;
			}
			if (ways[i] > 0)
			{
				ptr_node->ant = j;
				j++;
				ways[i] -= 1;
			}
			else
				ptr_node->ant = 0;
			++i;
			ptr_path = ptr_path->next;
		}
		print_move(graph, info, j);
	}
}

void				print_graph(t_graph **graph, t_info *info)
{
	int			i;
	t_link		*temp;

	i = 0;
	printf("%d\n", info->count_ants);
	while (i < info->count_node)
	{
		printf("%s %d %d\n", graph[0][i].name, graph[0][i].x, graph[0][i].y);
		i++;
	}
	i = 0;
	while (i < info->count_node)
	{
		temp = graph[0][i].link;
		while (temp)
		{
			printf("%s-%s\n", graph[0][i].name, graph[0][temp->node].name); //two print link
			temp = temp->next;
		}
		++i;
	}
	printf("\n");
}
