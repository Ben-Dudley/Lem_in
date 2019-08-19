/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphs_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 15:27:17 by bdudley           #+#    #+#             */
/*   Updated: 2019/08/19 18:28:12 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_graph	*new_graph(char *name, t_link **link)
{
	t_graph *new;

	new = (t_graph *)malloc(sizeof(*new));
	new->name = name;
	new->link = link;
	new->next = NULL;
	return (new);
}

void add_graph(t_graph **graph, t_graph *new)
{
	new->next = *graph;
	*graph = new;
}

void	free_graph(t_graph **graph)
{
	t_graph *ptr;

	while (*graph)
	{
		free((*graph)->name);
		(*graph)->name = NULL;
		if ((*graph)->link)
			free_link((*graph)->link);
		ptr = *graph;
		*graph = (*graph)->next;
		free(ptr);
		ptr = NULL;
	}
}