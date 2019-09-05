/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   score_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 17:32:54 by bdudley           #+#    #+#             */
/*   Updated: 2019/09/05 20:33:06 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void					reverse_node(t_path **path)
{
	t_node				*ptr;
	t_node				*temp;

	temp = (*path)->node;
	ptr = NULL;
	while (temp->next && temp->next->next)
	{
		temp = temp->next->next;
		((*path)->node)->next->next = (*path)->node;
		((*path)->node) = ((*path)->node)->next;
		((*path)->node)->next->next = ptr;
		ptr = (*path)->node;
		(*path)->node = temp;
	}
	if ((*path)->node->next)
	{
		temp = temp->next;
		temp->next = (*path)->node;
		temp->next->next = ptr;
		(*path)->node = temp;
	}
	else
		(*path)->node->next = ptr;
}

void					reverse_list(t_graph **graph, t_info *info)
{
	t_path				*ptr;
	t_path				*temp;

	temp = info->path;
	ptr = NULL;
	while (temp->next && temp->next->next)
	{
		temp = temp->next->next;
		(info->path)->next->next = info->path;
		(info->path) = (info->path)->next;
		(info->path)->next->next = ptr;
		ptr = info->path;
		info->path = temp;
	}
	if (info->path->next)
	{
		temp = temp->next;
		temp->next = info->path;
		temp->next->next = ptr;
		info->path = temp;
	}
	else
		info->path->next = ptr;
}

void					del_flow(t_graph **graph, t_info *info, int count)
{
	t_path				*ptr;
	t_path				*temp;

	ptr = info->path;
	temp = ptr;
	while (ptr)
	{
		if (ptr->stack != count)
		{
			if (temp == ptr)
			{
				info->path = info->path->next;
				temp = info->path;
			}
			else
				temp->next = ptr->next;
			free(ptr);
			ptr = temp;
		}
		else
		{
			temp = ptr;
			ptr = ptr->next;
		}
	}
}

int						distribution_ants(int **ways, int score_ants,
											int count_ways, int size)
{
	int					j;

	j = 0;
	while (j < count_ways && score_ants > 0)
	{
		ways[0][j] += size;
		score_ants -= size;
		++j;
	}
	return (score_ants);
}

int						difference_length_path(t_info *info, int **ways)
{
	t_path				*ptr;
	int					j;
	int					i;
	int					score_ants;

	score_ants = info->count_ants;
	ptr = info->path;
	i = 0;
	while (score_ants > 0 && ptr->next)
	{
		j = 0;
		while (j <= i)
		{
			ways[0][j] += ptr->next->length - ptr->length;
			score_ants -= ptr->next->length - ptr->length;
			++j;
		}
		++i;
		ptr = ptr->next;
	}
	return (score_ants);
}

void					score_ways(t_graph **graph, t_info *info,
													int count_ways)
{
	int					*ways;
	int					i;
	int					score_ants;

	reverse_list(graph, info);
	if (!(ways = (int *)malloc(sizeof(int) * count_ways)))
		error_message(graph, info, 0);
	i = 0;
	while (i < count_ways)
		ways[i++] = 0;
	if (count_ways > 1)
	{
		score_ants = difference_length_path(info, &ways);
		score_ants = distribution_ants(&ways, score_ants, count_ways,
							score_ants / count_ways);
		distribution_ants(&ways, score_ants, count_ways, 1);
	}
	else
		ways[0] = info->count_ants;
	steps_ants(graph, info, ways, count_ways);
}

int						score_ants(t_graph **graph, t_info *info, int count) //rename score_stack
{
	int					steps;
	int					length_mf;
	int					count_ants;
	t_path				*ptr;

	ptr = info->path;
	steps = 0;
	length_mf = 0;
	while (ptr)
	{
		if (ptr->stack == info->max_flow)
		{
			length_mf += ptr->length;
			steps += ptr->length;
		}
		else
			steps -= ptr->length;
		ptr = ptr->next;
	}
	if (steps <= 0)
		error_message(graph, info, 69);
	count_ants = steps * info->max_flow - length_mf;
	del_flow(graph, info, (info->max_flow > count_ants) ? 0 : info->max_flow);
	return ((info->max_flow > count_ants) ? count : info->max_flow);
}
