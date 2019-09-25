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

static int			init_mass(t_info *info, int *queue, int *traces)
{
	int			i;

	i = 1;
	queue[0] = info->ind_start;
	while (i <= info->count_node)
		queue[i++] = -1;
	i = 0;
	while (i <= info->count_node)
		traces[i++] = -1;
	return (-1);
}

static int			find_index(t_info *info, int *queue, int node)
{
	int		j;

	j = 0;
	while (j <= info->count_node)
	{
		if (queue[j] == node)
			break ;
		j++;
	}
	return (j);
}
void				in_stack_add(t_graph **graph, t_info *info, int stack, t_path *path)
{
	t_stack		*temp;
	int			i;

	i = 0;
	temp = info->stack;
	//printf("PUPA in_in_stack_add\n");
	while (temp)
	{
		if (temp->stack == stack)
		{
			add_path(&temp->path, new_path(graph, info));
			i += 1;
			break ;
		}// add path сюда
		temp = temp->next;
	}
	if (i == 0)
	{
		add_stack(&info->stack, new_stack(graph, info, stack, path));
	}

}

static int			get_path(t_graph **graph, t_info *info, int *traces,
						int flag)
{
	if (flag)
	{
		save_path(graph, info, traces, info->ind_end);
		--info->path->length;
		info->path->stack = info->max_flow;
		reverse_node(&info->path);
	}
	else
		restoration_path(graph, info, traces);
	return (1);
}

int					find_path(t_graph **graph, t_info *info,
						int *queue, int *traces)
{
	int			i;
	int			j;
	t_link		*ptr;
	int			weight;
//	int			z  = 0; // delete
	weight = 0;
	i = init_mass(info, queue, traces);
	j = 0;
	while (queue[++i] != -1)
	{
		ptr = graph[0][queue[i]].link;
		if (queue[i] == info->ind_start)
			graph[0][queue[i]].weight = weight;
		if (graph[0][queue[i]].weight == weight)
			weight = weight + 1;
		while (ptr)
		{
			if (weight < graph[0][ptr->node].weight)
			{
				graph[0][ptr->node].weight = weight;
				//printf("%d - имя(%s)\n", graph[0][ptr->node].weight, graph[0][ptr->node].name);
			}
			if (ptr->status != 0 && graph[0][ptr->node].visited == 0)
				if (find_index(info, queue, ptr->node) == info->count_node + 1)
				{
					queue[++j] = ptr->node;
				//	printf("ptr->node %d\n", ptr->node);
					traces[ptr->node] = queue[i];
					if (ptr->node == info->ind_end)
						return (get_path(graph, info, traces,
								(info->count_ants > 0) ? 1 : 0));
				}
			//printf("times\n");
			ptr = ptr->next;
		}
	//	printf("\n");
	}
//	while (queue[z])
	//	printf("queue %d", queue[z++]);
	//printf("\n");
	return (0);
}
