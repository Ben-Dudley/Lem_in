/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 14:14:51 by bdudley           #+#    #+#             */
/*   Updated: 2019/08/30 20:42:26 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

void		save_path(t_graph **graph, t_info *info, int *traces)
{
	int i;
	t_link *temp;
	t_path *path;

	i = info->ind_end;
	//printf("VREDNII ZEN~YA POKERMAN\n");
	//print_queue(graph,traces,info->count_node);
	path = new_path(graph, info);
	while (i != info->ind_start)
	{
		//print(graph, info, i);
		temp = graph[0][traces[i]].link;
		while (temp)
		{
			if (temp->node == i)
			{
				if (i != info->ind_end)
					graph[0][temp->node].visited = 1;
				temp->status = 0;
				//complete_node(graph, temp->node);
				add_node(&path->node, new_node(graph, info, temp->node));
				++path->length;
				break;
			}
			temp = temp->next;
		}
		i = traces[i];
	}
	add_node(&path->node, new_node(graph, info, i));
	//printf("length %d\n", path->length);
	--path->length;
	if (path->length == -1)
		free(path);
	else
	{
		path->stack = info->max_flow;
		add_path(&info->path, path); // poka tak
	}

}
void		clear_graph(t_graph **graph, t_info *info)
{
	int	i;
	t_link	*temp;

	i = 0;
	//print_massiv(graph, info);
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
//	printf("Print massiv after clear\n");
//	print_massiv(graph, info);
}
