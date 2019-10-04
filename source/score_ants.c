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

int						difference_length_path(t_info *info, int **ways, int *used_path)
{
	t_path				*ptr;
	int					j;
	int					score_ants;

	score_ants = info->count_ants;
	ptr = info->path;
	*used_path = 1;
	while (ptr->next && score_ants >= ptr->next->length - ptr->length && score_ants >= *used_path * (ptr->next->length - ptr->length))
	{
		j = 0;
		//printf("difference %d used_path %d score_ants %d\n", ptr->next->length - ptr->length, *used_path, score_ants);
		while (j < *used_path)
		{

			ways[0][j] += (ptr->next->length - ptr->length) > score_ants ?
						  score_ants : (ptr->next->length - ptr->length);
			score_ants -= (ptr->next->length - ptr->length) > score_ants ?
							score_ants : (ptr->next->length - ptr->length);
			++j;
		//	print_ways(info, *ways, 14);

		}
		++(*used_path);
		ptr = ptr->next;
	}

	//printf("ways[0] %d %d\n", score_ants, ways[0][0]);
	return (score_ants);
}

void			print_ways(t_info *info, int *ways, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		printf(" %d ", ways[i]);
		++i;
	}
	printf("\n");
}

void					score_ways(t_graph **graph, t_info *info,
													int count_ways)
{
	int					*ways;
	int					i;
	int					score_ants;
	int 				used_path;

	reverse_list(graph, info);
	if (!(ways = (int *)malloc(sizeof(int) * count_ways)))
		error_message(graph, info, 0);
	i = 0;
	while (i < count_ways)
		ways[i++] = 0;
	ft_print_pyti(graph, info);
	if (count_ways > 1)
	{
		score_ants = difference_length_path(info, &ways, &used_path);
		score_ants = distribution_ants(&ways, score_ants, used_path,
							score_ants / used_path);
		distribution_ants(&ways, score_ants, used_path, 1);
	}
	else
		ways[0] = info->count_ants;
	//print_ways(info, ways, 6);
	steps_ants(graph, info, ways, count_ways);
}

int						score_ants(t_graph **graph, t_info *info, int count)
{//rename score_stack
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
	del_flow(graph, info, (info->count_ants > count_ants) ? info->max_flow : 0);
	return ((info->count_ants > count_ants) ? info->max_flow : count);
}
