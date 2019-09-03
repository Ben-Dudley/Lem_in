/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharrold <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 15:30:15 by hharrold          #+#    #+#             */
/*   Updated: 2019/09/02 15:30:18 by hharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		print(t_graph **graph, t_info *info)
{
	int			i;
	t_link		*temp;

	i = 0;
	ft_putnbr(info->count_ants); /*колличество муравьев*/
	while (i < info->count_node)
	{
		ft_putstr(graph[0][i].name);
		ft_putchar(' ');
		ft_putnbr(graph[0][i].x);
		ft_putchar(' ');
		ft_putnbr(graph[0][i].y);
		ft_putchar('\n');
		i++;
	}
	i = 0;
	while (i < info->count_node)
	{
		temp = graph[0][i].link;
		while (temp)
		{
			ft_putstr(graph[0][i].name);
			ft_putchar('-');
			ft_putstr(graph[0][temp->node].name);
			ft_putchar('\n');
			temp = temp->next; // убрать двойной вывод или как то так
		}
		++i;
	}
	ft_putchar('\n'); // нафига
}

void		print_ant_in_room(int ant, char *name_room) // и данные 
{ //о последнем муравье чтобы не ставить пробел
	ft_putchar('L');
	ft_putnbr(ant);
	ft_putchar('-');
	ft_putstr(name_room);
	if (1) // вот сюда данные запихать
		ft_putchar(' ');
	//ft_putchar('\n');
}
