/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 14:14:51 by bdudley           #+#    #+#             */
/*   Updated: 2019/09/06 10:32:10 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Save path and restoration path for traces.
** Clear graph.
** Reverse list and pat.
*/

static void			sup_add_stack(t_graph **graph, t_info *info,
															t_path *path, int i)
{
	add_node(&path->node, new_node(graph, info, i)); // это не фришится
	if (!info->stack)
		info->stack = new_stack(graph, info, 0, path);
	else
		add_path(&(info->stack->path), path);
}

void				save_path(t_graph **graph, t_info *info,
												t_trace *trace, int i)
{
	t_link			*temp;
	t_path			*path;
	t_node			*n_node;
	int				st;

	path = new_path(graph, info);
	while (i != info->ind_start)
	{
		temp = graph[0][trace->traces_0[i]].link;
		while (temp)
		{
			if (temp->node == i)
			{
				if (i != info->ind_end)
					graph[0][temp->node].visited = 1;
				temp->status = 0;
				n_node = new_node(graph, info, temp->node);
				add_node(&path->node, n_node);
	//			free(n_node);
				++path->length;
				break ;
			}
			temp = temp->next;
		}
		i = trace->traces_0[i];
	}
	sup_add_stack(graph, info, path, i);
	//free(path);
}

void				reverse_node(t_path **path)
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

static void			sup_rev_temp(t_path **temp, t_stack **stack, t_path **ptr)
{// не надо ли случаем &
	((*stack)->path)->next->next = (*stack)->path;
	((*stack)->path) = ((*stack)->path)->next;
	((*stack)->path)->next->next = *ptr;
	*ptr = (*stack)->path;
	(*stack)->path = *temp;
}

void				reverse_list(t_graph **graph, t_info *info)
{
	t_path				*ptr;
	t_path				*temp;
	t_stack				*stack;

	stack = info->stack;
	while (stack)
	{
		temp = stack->path;
		ptr = NULL;
		while (temp->next && temp->next->next)
		{
			temp = temp->next->next;
			sup_rev_temp(&temp, &stack, &ptr);
		}
		if (stack->path->next)
		{
			temp = temp->next;
			temp->next = stack->path;
			temp->next->next = ptr;
			stack->path = temp;
		}
		else
			stack->path->next = ptr;
		stack = stack->next;
	}
}
