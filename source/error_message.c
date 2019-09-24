/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 15:33:37 by hharrold          #+#    #+#             */
/*   Updated: 2019/09/20 13:18:55 by bdudley          ###   ########.fr       */
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
			free(path->node);
			path->node = ptr;
		}
		free(path);
		path = temp;
	}
}

static void		free_stack(t_stack *stack)
{
	t_stack		*temp;
	t_node		*ptr;

	while (stack)
	{
		temp = stack->next;
		free(stack);
		stack = temp;
	}
}

void			free_graph(t_graph **graph, t_info *info)
{
	int		i;
	t_link	*temp;

	i = 0;
	while (i < info->count_node)
	{
		while (graph[0][i].link)
		{
			temp = graph[0][i].link;
			graph[0][i].link = (graph[0][i].link)->next;
			free(temp);
			temp = NULL;
		}
		++i;
	}
	free_stack(info->stack);
	free_path(info->path);
}
void			error_arg(t_graph **graph, t_info *info, int code_error)
{
	if (code_error == 21)
		ft_putstr("Bad Flag\n");
}

void			help_error(t_graph **graph, t_info *info, int code_error)
{
	if (code_error == 5)
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
	else if (code_error == 11)
		ft_putstr("A vertex with this name already exists\n");
	else if (code_error == 69)
		ft_putstr("Path not found\n");
	else if (code_error == 50)
		ft_putstr("Invalid input\n");
	else if (code_error == 77)
		ft_putstr("The vertex name cannot start with character 'L'\n");
	else
		error_arg(graph, info, code_error);
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
		ft_putstr("Usage:  For start ./lem-in < file_name.txt. "
		"First to enter ant.\n"
		"Next room (format: name x y) with room ##start and room ##end.\n"
		"Last add link between rooms.\n");
	else
		help_error(graph, info, code_error);
	free_graph(graph, info);
	exit(3);
}
