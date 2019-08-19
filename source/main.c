/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 16:29:59 by bdudley           #+#    #+#             */
/*   Updated: 2019/08/19 21:32:26 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	error(char *str, t_graph **graph, t_info **info)
{
	free(*info);
	free_graph(graph);
	ft_putstr(str);
	exit(3);
}

void	init(t_graph **graph, t_info **info)
{
	*graph = NULL;
	*info = (t_info *)malloc(sizeof(**info));
	(*info)->count_ants = 0;
}

int main()
{
	t_graph *graph;
	t_info	*info;

	init(&graph, &info);
	get_ants(&graph, &info);
	get_rooms_links(&graph, &info);
	printf("Count of ants %d", info->count_ants);
	error("OK! =^_^=\n", &graph, &info);
	return (0);
}