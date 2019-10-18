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
			free_path(ptr);
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
	t_path *ptr;
	if (!info->stack)
	{

		//printf("%d)New_stack %d\n", info->max_flow, path->length);
		//printf("New_stack\n");
		info->stack = new_stack(graph, info, info->max_flow, path);
	}
	else if (info->stack->stack != info->max_flow)
	{
		//printf("%d)Add_stack %d\n", info->max_flow, path->length);
		add_stack(&info->stack,
				  new_stack(graph, info, info->max_flow, path));
	}
	else
	{

		//printf("%d)Add_path %d\n", info->max_flow, path->length);
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

void get_path_numbers(t_graph **graph, t_info *info)
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
//		if (info->max_flow == 11)
//		for_fix_stack(graph, info);
		//printf("pppp\n");
		while (temp)// && temp->node != info->ind_end)
		{
			//printf("!!! %d (%d-%d)\n", temp->node, temp->status, temp->reverse->status);
			if (temp->status == 0 && temp->reverse->status == 1 && graph[0][temp->node].weight != 0)
			{
				add_node(&path->node, new_node(graph, info, temp->node));
				++path->length;
				if (temp->node != info->ind_end)
					graph[0][temp->node].weight = 0;
				else
				{
					//--path->length;
					temp->status = -7;
					break ;
				}
				temp = graph[0][temp->node].link;
			}
			else
				temp = temp->next;
		}
	//	add_node(&path->node, new_node(graph, info, info->ind_end));
		for_add_in_stack(graph, info, path);
	}
}
