/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 01:25:42 by bdudley           #+#    #+#             */
/*   Updated: 2018/12/15 01:26:48 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	quicksort(char ***a, int first, int last)
{
	int		i;
	int		j;
	char	*command;
	char	*tmp;

	i = first;
	j = last;
	command = a[0][(i + j) >> 1];
	if (first > last)
		return ;
	while (i <= j)
	{
		while (ft_strcmp(a[0][i], command) < 0)
			i++;
		while (ft_strcmp(a[0][j], command) > 0)
			j--;
		if (i <= j)
		{
			tmp = a[0][i];
			a[0][i++] = a[0][j];
			a[0][j--] = tmp;
		}
	}
	quicksort(a, first, j);
	quicksort(a, i, last);
}
