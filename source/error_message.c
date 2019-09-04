/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharrold <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 15:33:37 by hharrold          #+#    #+#             */
/*   Updated: 2019/09/02 15:33:41 by hharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		free_path(t_path *path)
{
	t_path		*temp;
	t_node		*ptr;

	while (path)
	{
		temp = path->next;
		while (path->node)
		{
			ptr = path->node->next;
			free (path->node);
			path->node = ptr;
		}
		free (path);
		path = temp;
	}
}

static void		free_graph(t_graph **graph, t_info *info)
{
    int		i;
    t_link	*temp;

    i = 0;
    while (i < info->count_node) // (ну типо колличество графов)
	{
		temp = graph[0][i].link;
		while (temp)
		{
			temp = graph[0][i].link->next;
			free (graph[0][i].link);
			graph[0][i].link = temp->next;
		}	
	//	free (graph[0][i]); // фришится или нет надо ли
		++i;
	}
	free_path(info->path);
	//free (info);  // надо ли фришится или нет
}

int				error_message(t_graph **graph, t_info *info, int code_error)
{
	if (code_error == 0)
		ft_putstr("Memory allocation error\n");
	else if (code_error == 1)
		ft_putstr("It is impossible to translate ants\n");
	else if (code_error == 2)
		ft_putstr("Insufficient data for processing\n");
	else if (code_error == 3)
		ft_putstr("Such a room does not exist in the graph. Unable\
		to create path\n");
	else if (code_error == 4)
		ft_putstr("Empty File\n");
	else if (code_error == 5)
		ft_putstr("It is impossible to translate ants\n");
	else if (code_error == 6)
		ft_putstr("The number of ants can only be positive\n");
	else if (code_error == 7)
		ft_putstr("First you need to enter the number of ants\n");
	else if (code_error == 8)
		ft_putstr("You want to enter a number of type integer\n");
	else if (code_error == 9)
		ft_putstr("You entered nothing\n");
	else if (code_error == 10)
		ft_putstr("Invalid input\n");
	else if (code_error == 10)
		ft_putstr("Invalid input\n");
	else if (code_error == 10)
		ft_putstr("Invalid input\n");
	free_graph(graph, info);
	exit (0);
}
