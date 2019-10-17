/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 16:09:50 by bdudley           #+#    #+#             */
/*   Updated: 2019/09/05 19:42:16 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Here is search shortest paths stack.
** Here is also counts the numbers max flow.
*/

int		init_mass(t_info *info, t_trace *trace)
{
	int			i;

	i = 1;
	(trace->queue)[0] = info->ind_start;
	while (i <= info->count_node)
		(trace->queue)[i++] = -1;
	i = 0;
	while (i <= info->count_node)
		(trace->traces_0)[i++] = -1;
	i = 0;
	while (i <= info->count_node)
		(trace->traces_1)[i++] = -1;
	(trace->traces_0)[info->ind_start] = info->ind_start;
	(trace->traces_1)[info->ind_start] = info->ind_start;
	return (-1);
}

int		find_index(t_info *info, t_trace *trace, int node)
{
	int		j;

	j = 0;
	while (j <= info->count_node)
	{
		if ((trace->queue)[j] == node)
			break ;
		j++;
	}
	return (j);
}

static int		get_path(t_graph **graph, t_info *info, t_trace *trace,
						int flag)
{
	if (flag)
	{
		printf("Save path\n");
		save_path(graph, info, trace, info->ind_end);
		--info->stack->path->length;
		reverse_node(&info->stack->path);
	}
	else
		restoration_path(graph, info, trace);
	return (1);
}

int				rewrite_queue(t_info *info, t_trace *trace, int j, int node)
{
	int			i;

	i = 0;
	while ((trace->queue)[i] != node)
		i++;
	while ((trace->queue)[i] != -1)
	{
		(trace->queue)[i] = (trace->queue)[i + 1];
		i++;
	}
	return (j - 1);
}

int				find_path(t_graph **graph, t_info *info,
													t_trace *trace)
{
	int			ij[2];
	t_link		*ptr;

	ij[0] = init_mass_and_clear_end_link_weight(graph, info, trace);
	ij[1] = 0;
	while ((trace->queue)[++(ij[0])] != -1)
	{
		ptr = graph[0][(trace->queue)[ij[0]]].link;
		while (ptr)
		{
			if (check_visited(graph, ptr, trace, ij[0]))
			{
				if (not_node(info, ptr, trace, ij[0]))
				{
					ij[1] -= 1;
					ij[0] = rewrite_queue(info, trace, ij[0], ptr->node);
				}
				ij[1] = algorithm(graph, ptr, trace, ij);
				if (ptr->node == info->ind_end)
					return (get_path(graph, info, trace, 0));
			}
			ptr = ptr->next;
		}
	}
	return (0);
}
