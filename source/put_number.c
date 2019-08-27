/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_number.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharrold <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 19:22:39 by hharrold          #+#    #+#             */
/*   Updated: 2019/08/27 19:22:41 by hharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			put_number(char *str, t_graph **graph, t_info *info)
{
	int	number;
	int	flag;
	int	off;
	int	lim;

	number = 0;
	flag = 1;
	if (*str == '-' || *str == '+')
		flag = (*str++ == '-') ? -1 : 1;
	if (*str == '\0')
		error("You entered nothing\n", graph, info);
	off = flag == 1 ? 2147483647 : -2147483648;
	lim = flag * (off % 10);
	off /= flag * 10;
	while (*str != '\0')
	{
		if (*str > '9' || *str < '0' || number * flag > off
			|| (flag * number == off && (*str - '0') > lim))
			error("You want to enter a number of type integer\n", graph, info);
		number = number * 10 + flag * (*str - '0');
		str++;
	}
	return (number);
}
