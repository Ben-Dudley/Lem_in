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

void		del_flow(t_info *info, int count, t_stack *ptr, t_stack *temp)
{
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
