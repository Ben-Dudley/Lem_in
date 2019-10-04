/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharrold <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 18:11:04 by hharrold          #+#    #+#             */
/*   Updated: 2019/10/03 18:11:51 by hharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		length(t_link *head)
{
	int		count;
	t_link	*current;

	count = 0;
	current = head;
	while (current != NULL)
	{
		count += 1;
		current = current->next;
	}
	return (count);
}

static t_link	*sortedmerge(t_graph **graph, t_link *a, t_link *b)
{
	t_link *result;

	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (graph[0][a->node].weight <= graph[0][b->node].weight)
	{
		result = a;
		result->next = sortedmerge(graph, a->next, b);
	}
	else
	{
		result = b;
		result->next = sortedmerge(graph, a, b->next);
	}
	return (result);
}

static void		front_back_split(t_link *source, t_link **frontref,
												t_link **backref)
{
	int			len;
	int			i;
	t_link		*current;
	int			hopcount;

	current = source;
	len = length(source);
	i = 0;
	if (len < 2)
	{
		*frontref = source;
		*backref = NULL;
	}
	else
	{
		hopcount = (len - 1) / 2;
		while (i < hopcount)
		{
			current = current->next;
			i += 1;
		}
		*frontref = source;
		*backref = current->next;
		current->next = NULL;
	}
}

static void		merge_sort_helper(t_graph **graph, t_link **base)
{
	t_link	*link;
	t_link	*a;
	t_link	*b;

	link = *base;
	if ((link == NULL) || (link->next == NULL))
		return ;
	front_back_split(link, &a, &b);
	merge_sort_helper(graph, &a);
	merge_sort_helper(graph, &b);
	*base = sortedmerge(graph, a, b);
}

void			merge_sort(t_graph **graph, t_info *info)
{
	int		i;

	i = 0;
	while (i < info->count_node)
	{
		merge_sort_helper(graph, &graph[0][i].link);
		i += 1;
	}
}
