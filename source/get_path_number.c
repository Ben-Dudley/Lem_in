/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_number.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharrold <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 09:55:56 by hharrold          #+#    #+#             */
/*   Updated: 2019/10/06 09:56:00 by hharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			for_add_in_stack(t_graph **graph, t_info *info, t_path *path)
{
	t_path *ptr;

	if (!info->stack)
		info->stack = new_stack(graph, info, info->max_flow, path);
	else if (info->stack->stack != info->max_flow)
		add_stack(&info->stack, new_stack(graph, info, info->max_flow, path));
	else
	{
		ptr = info->stack->path;
		if (path->length < ptr->length)
		{
			path->next = ptr;
			info->stack->path = path;
			return ;
		}
		while (ptr->next && path->length > ptr->next->length)
			ptr = ptr->next;
		if (ptr->next == NULL && path->length > ptr->length)
			ptr->next = path;
		else
		{
			add_path(&ptr->next, path);
			ptr->next = path;
		}
	}
}

static int		if_status(t_graph **graph, t_info *info,
								t_link *temp, t_path *path)
{
	if (temp->status == 0 && temp->reverse->status == 1
		&& graph[0][temp->node].weight != 0)
	{
		add_node(&path->node, new_node(graph, info, temp->node));
		if (temp->node != info->ind_end)
			graph[0][temp->node].weight = 0;
		else
		{
			temp->status = -7;
		}
		return (1);
	}
	return (0);
}

void			get_path_numbers(t_graph **graph, t_info *info)
{
	t_link			*temp;
	t_path			*path;
	int				i;

	i = 0;
	while (++i <= info->max_flow)
	{
		temp = graph[0][info->ind_start].link;
		path = new_path(graph, info);
		add_node(&path->node, new_node(graph, info, info->ind_start));
		while (temp)
		{
			if (if_status(graph, info, temp, path))
			{
				++path->length;
				if (!(temp->node != info->ind_end))
					break ;
				temp = graph[0][temp->node].link;
			}
			else
				temp = temp->next;
		}
		for_add_in_stack(graph, info, path);
	}
}
