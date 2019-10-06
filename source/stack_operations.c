/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharrold <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 09:55:56 by hharrold          #+#    #+#             */
/*   Updated: 2019/10/06 09:56:00 by hharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		add_stack(t_stack **stack, t_stack *new)
{
	new->next = *stack;
	*stack = new;
}

t_stack		*new_stack(t_graph **graph, t_info *info, int stack, t_path *path)
{
	t_stack		*new;

	if (!(new = ((t_stack *)malloc(sizeof(*new)))))
		error_message(graph, info, 0);
	new->stack = stack;
	new->path = path;
	new->next = NULL;
	return (new);
}

void		del_flow(t_graph **graph, t_info *info, int count)
{
	t_stack				*ptr;
	t_stack				*temp;

	ptr = info->stack;
	temp = ptr;
	while (ptr)
	{
		if (ptr->stack != count)
		{
			if (temp == ptr)
			{
				info->stack = info->stack->next;
				temp = info->stack;
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

void		for_add_in_stack(t_graph **graph, t_info *info, t_path *path)
{
	if (info->stack->stack != info->max_flow)
		add_stack(&info->stack,
			new_stack(graph, info, info->max_flow, path));
	else
		add_path(&info->stack->path, path);
	add_node(&path->node, new_node(graph, info, info->ind_start));
}

void		get_path_numbers(t_graph **graph, t_info *info)
{
	t_link			*temp;
	t_path			*path;
	int				i;

	i = 0;
	while (++i <= info->max_flow)
	{
		temp = graph[0][info->ind_start].link;
		path = new_path(graph, info);
		for_add_in_stack(graph, info, path);
		while (temp && temp->node != info->ind_end)
		{
			if (graph[0][temp->node].visited == i)
			{
				add_node(&path->node, new_node(graph, info, temp->node));
				++path->length;
				temp = graph[0][temp->node].link;
			}
			else
				temp = temp->next;
		}
		add_node(&path->node, new_node(graph, info, info->ind_end));
	}
}
