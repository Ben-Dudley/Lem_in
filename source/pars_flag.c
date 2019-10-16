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

void					print_flags(t_info *info)
{
	int 	i;

	i = 0;
	if (info->flag_score > 0)
	{
		if (info->flag_colour)
			ft_putstr("\033[1;32m");
		ft_putnbr(info->flag_score - 1);
		ft_putstr(" step");
		if ((info->flag_score - 1) > 1)
			ft_putstr("s");
		ft_putstr("\n");

	}
	if (info->flag_score_in_file != 0)
	{
		if (info->flag_colour)
			ft_putstr("\033[1;33m");
		while (info->basic_information && info->basic_information[i] != '\n')
			write(1, &info->basic_information[i++], 1);
		write(1, "\n", 1);
		free(info->basic_information);
	}
}

void					writer_base(t_info *info, char *line)
{
	char	*temp;
	char	*temp2;

	temp = info->basic_information;
	temp2 = ft_strjoin(line, "\n");
	info->basic_information = ft_strjoin(info->basic_information, temp2);
	if (*temp2)
		free (temp2);
	if (*temp)
		free (temp);
}

static int				pars_flag(char c, t_info *info)
{
	if (c == 'v')
		info->flag_visual = 1;
	else if (c == 'c')
		info->flag_colour = 1;
	else if (c == 's')
		info->flag_score = 1;
	else if (c == 'p')
		info->flag_way = 1;
	else if (c == 'a')
		info->flag_all_way = 1;
	else if (c == 'g')
		info->flag_print_graph = 1;
	else if (c == 'S')
		info->flag_score_in_file = 1;
	else
		return (0);

	return (1);
}

static int				check_flag(char *av, t_info *info)
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

int						flag_checking(int ac, char **av, t_graph **graph,
														t_info *info)
{
	int			counter;

	counter = 1;
	if (ac < 1)
		return (0);
	while (ac > counter)
	{
		if (check_flag(av[counter], info))
			++counter;
		else
		{
			error_message(graph, info, 21);
			return (0);
		}
	}
	return (1);
}
