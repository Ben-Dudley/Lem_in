/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 21:02:11 by bdudley           #+#    #+#             */
/*   Updated: 2019/02/22 17:36:19 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_nbr(int n, int fd)
{
	if (n / 10 == 0)
		ft_putchar_fd(n + '0', fd);
	else
	{
		ft_nbr(n / 10, fd);
		ft_nbr(n % 10, fd);
	}
}

void		ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
	}
	if (n >= 0)
		ft_nbr(n, fd);
}
