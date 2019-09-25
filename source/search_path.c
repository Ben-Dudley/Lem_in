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

void				restoration_path(t_graph **graph, t_info *info, int *traces)
{
	int			i;
	t_link		*temp;

	i = info->ind_end;
	while (i != info->ind_start)
	{
		temp = graph[0][traces[i]].link;
		while (temp)
		{
			if (temp->node == i)
			{
				temp->status = 0;
				break ;
			}
			temp = temp->next;
		}
		i = traces[i];
	}
}

void				save_path(t_graph **graph, t_info *info, int *traces, int i)
{
	t_link			*temp;
	t_path			*path;

	path = new_path(graph, info);
	while (i != info->ind_start)
	{
		temp = graph[0][traces[i]].link;
		while (temp)
		{
			if (temp->node == i)
			{
				if (i != info->ind_end)
					graph[0][temp->node].visited = 1;
				temp->status = 0;
				add_node(&path->node, new_node(graph, info, temp->node));
				printf("save)path  %d - (%s)\n", path->node->node, graph[0][path->node->node].name);
				++path->length;
				break ;
			}
			temp = temp->next;
		}
		i = traces[i];
	}
	//printf("PUPA in safe_path\n");

	add_node(&path->node, new_node(graph, info, i));
	add_path(&info->path, path);
	in_stack_add(graph, info, info->path->stack, path); // stack == info->path->stack'????
}

void				clear_graph(t_graph **graph, t_info *info)
{
	int				i;
	t_link			*temp;

	i = 0;
	while (i < info->count_node)
	{
		temp = graph[0][i].link;
		while (temp)
		{
			graph[0][temp->node].visited = 0;
			if (!(temp->reverse->status == 0 && temp->status == 0))
				temp->status = 1;
			temp = temp->next;
		}
		++i;
	}
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

void				reverse_list(t_graph **graph, t_info *info)
{
	t_path				*ptr;
	t_path				*temp;

	temp = info->path;
	ptr = NULL;
	while (temp->next && temp->next->next)
	{
		temp = temp->next->next;
		(info->path)->next->next = info->path;
		(info->path) = (info->path)->next;
		(info->path)->next->next = ptr;
		ptr = info->path;
		info->path = temp;
	}
	if (info->path->next)
	{
		temp = temp->next;
		temp->next = info->path;
		temp->next->next = ptr;
		info->path = temp;
	}
	else
		info->path->next = ptr;
}
