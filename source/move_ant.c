/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ant.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 17:15:22 by bdudley           #+#    #+#             */
/*   Updated: 2019/09/19 21:34:54 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int					min_score_ants(t_info *info, int count,
												int count_ways)
{
	int			min;
	int			ant;
	t_path		*temp;

	ant = 0;
	temp = info->stack->path;
	min = count;
	while (temp)
	{
		if (temp->length != 0)
			ant = temp->node->next->ant - (count_ways * (temp->length - 1));
		if (min > ant)
			min = ant;
		temp = temp->next;
	}
	return (min);
}

static int			step(int *ways, t_path **ptr_path, t_info *info, int *j)
{
	t_node		*ptr_node;
	int			score_ants;

	score_ants = 0;
	ptr_node = (*ptr_path)->node;
	if (ptr_node->node && !ptr_node->next->node)
		score_ants += 1;
	while (ptr_node->next->node != info->ind_start)
	{
		ptr_node->ant = ptr_node->next->ant;
		if (ptr_node->node == info->ind_end && ptr_node->next->ant != 0)
			score_ants += 1;
		ptr_node = ptr_node->next;
	}
	if (*ways > 0)
	{
		ptr_node->ant = *j;
		(*j)++;
		*ways -= 1;
	}
	else
		ptr_node->ant = 0;
	*ptr_path = (*ptr_path)->next;
	return (score_ants);
}

void				steps_ants(t_graph **graph, t_info *info,
										int *ways, int count_ways)
{
	int			j;
	int			i;
	int			score_ants;
	t_path		*ptr_path;

	j = 1;
	score_ants = 0;
	print_graph(graph, info);
	while (score_ants < info->count_ants)
	{
		i = 0;
		ptr_path = info->stack->path;
		while (ptr_path)
		{
			score_ants += step(&(ways[i]), &ptr_path, info, &j);
			++i;
		}
		print_move(graph, info, j, count_ways);
	}
}
