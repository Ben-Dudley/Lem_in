/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_flag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharrold <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 09:55:56 by hharrold          #+#    #+#             */
/*   Updated: 2019/09/20 09:56:00 by hharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int               pars_flag(char c, t_info *info)
{
	if (c == 'v')
		info->flag_visual = 1;
	else if (c == '-')
		info->flag_colour = 1;
	else if (c == 's')
		info->flag_score = 1;
	else if (c == 'p')
		info->flag_way = 1;
    else if (c == 'a')
		info->flag_all_way = 1;
    else if (c == 'g')
		info->flag_print_graph = 1;
	else
		return (0);
	return (1);
}

static int			check_flag(char *av, t_info *info)
{
	int		i;

	i = 0;
	if (av[i] == '-')
	{
		++i;
		if (av[i])
		{
			while (av[i] != '\0')
			{
				if (pars_flag(av[i], info))
					++i;
				else
					return (0);
			}
			return (1);
		}
	}
	return (0);
}

int					flag_checking(int ac, char **av, t_graph **graph,
                                                        t_info *info)
{
	int			counter;

	counter = 1;
	if (ac < 1)
		return (0);
	while (ac > counter)
	{
		if (!info->end_flag && check_flag(av[counter], info))
			++counter;
		else
		{
            error_message(graph, info, 21);
			return (0);
		}
	}
	return (1);
}