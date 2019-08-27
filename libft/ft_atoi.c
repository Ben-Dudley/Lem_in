/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 21:05:37 by bdudley           #+#    #+#             */
/*   Updated: 2019/02/22 20:07:13 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_atoi(const char *str)
{
	long	i;
	long	off;
	int		flag;
	long	lim;

	i = 0;
	flag = 1;
	while (*str == '\n' || *str == '\t' || *str == ' '
			|| *str == '\f' || *str == '\v' || *str == '\r')
		str++;
	if (*str == '-')
		flag = -1;
	off = flag == 1 ? 9223372036854775807 : (-9223372036854775807 - 1);
	lim = -(off % 10);
	off /= flag * 10;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (i * flag > off || (flag * i == off && (*str - '0') > lim))
			return (flag == 1 ? -1 : 0);
		i = i * 10 + flag * (*str - '0');
		str++;
	}
	return (i);
}
