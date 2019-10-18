/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   score_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 17:32:54 by bdudley           #+#    #+#             */
/*   Updated: 2019/09/19 22:12:57 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Select main stack and delete another.
** Distribution ways for ants.
*/

int			distribution_ants(int **ways, int score_ants,
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

int			difference_length_path(t_info *info, int **ways, int *used_path)
{
	t_path				*ptr;
	int					j;
	int					score_ants;

	score_ants = info->count_ants;
	ptr = info->stack->path;
	*used_path = 1;
	while (ptr->next && score_ants >= ptr->next->length - ptr->length
			&& score_ants >= *used_path * (ptr->next->length - ptr->length))
	{
		j = 0;
		while (j < *used_path)
		{
			ways[0][j] += (ptr->next->length - ptr->length) > score_ants ?
							score_ants : (ptr->next->length - ptr->length);
			score_ants -= (ptr->next->length - ptr->length) > score_ants ?
							score_ants : (ptr->next->length - ptr->length);
			++j;
		}
		++(*used_path);
		ptr = ptr->next;
	}
	return (score_ants);
}

void		score_ways(t_graph **graph, t_info *info, int count_ways)
{
	int				*ways;
	int				i;
	int				score_ants;
	int				used_path;

	if (!(ways = (int *)malloc(sizeof(int) * count_ways)))
		error_message(graph, info, 0);
	i = 0;
	while (i < count_ways)
		ways[i++] = 0;
	if (count_ways > 1)
	{
		score_ants = difference_length_path(info, &ways, &used_path);
		score_ants = distribution_ants(&ways, score_ants, used_path,
										score_ants / used_path);
		distribution_ants(&ways, score_ants, used_path, 1);
	}
	else
		ways[0] = info->count_ants;
	steps_ants(graph, info, ways, count_ways);
	free(ways);
}

int			score_step_in_ants(t_info *info, int steps, int *length_mf)
{
	t_path				*ptr;
	t_stack				*temp;

	temp = info->stack;
	ptr = temp->path;
	while (ptr)
	{
		if (temp->stack == info->max_flow)
		{
			*length_mf += ptr->length;
			steps += ptr->length;
		}
		else
			steps -= ptr->length;
		ptr = ptr->next;
		if (!ptr && temp->next)
		{
			temp = temp->next;
			ptr = temp->path;
		}
	}
	return (steps);
}

int			score_stack(t_info *info)
{
	int					steps;
	int					length_mf;
	int					count_ants;
	t_stack				*ptr;
	t_stack				*temp;

	steps = 0;
	length_mf = 0;
	ptr = NULL;
	temp = NULL;
	steps = score_step_in_ants(info, steps, &length_mf);
	count_ants = steps * info->max_flow - length_mf;
	del_flow(info, (info->count_ants > count_ants)
	? info->max_flow : info->max_flow - 1, ptr, temp);
	return ((info->count_ants > count_ants)
	? info->max_flow : info->max_flow - 1);
}
