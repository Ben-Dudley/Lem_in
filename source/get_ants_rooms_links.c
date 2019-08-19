/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ants_rooms_links.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 19:52:17 by bdudley           #+#    #+#             */
/*   Updated: 2019/08/19 22:54:37 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			put_number(char *str)
{
	int	number;
	int	flag;
	int	off;
	int	lim;

	number = 0;
	off = INT_MAX;
	lim = (off % 10);
	off /= 10;
	while (*str != '\0')
	{
		if (*str > '9' || *str < '0' || number > off
			|| (number == off && (*str - '0') > lim))
			return (-1);
		number = number * 10 + *str - '0';
		str++;
	}
	return (number);
}

void	get_ants(t_graph **graph, t_info **info)
{
	int number;
	char *line;

	while (get_next_line(0, &line, 0) > 0)
	{
		if (!(*line == '#' && *(line + 1) != '#'))
		{
			(*info)->count_ants = put_number(line);
			free(line);
			if ((*info)->count_ants < 0)
				error("Error: wrong number of ants. Good luck next time!\n", graph, info);
			return ;
		}
		free(line);
	}
}

char	*get_rooms(t_graph **graph, t_info **info)
{
	char *line;

	while (get_next_line(0, &line, 0) > 0)
	{
		if (*line == '#' && *(line + 1) == '#')
		{
			if (!ft_strcpy("##start\n", line))
			{
				free(line);
				get_next_line(0, &line, 0);
			}
		}
		else if (ft_strchr((const char*)(*line), ' ') != NULL)
		{

			return ;
		}
		else if (ft_strchr((const char*)(*line), '-') != NULL)
			return (line);
		free(line);
	}
}