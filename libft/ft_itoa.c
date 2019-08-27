/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 18:52:11 by bdudley           #+#    #+#             */
/*   Updated: 2019/02/22 17:27:45 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_length(int n)
{
	int length;

	length = 0;
	if (n < 0)
	{
		if (n == -2147483648)
			return (11);
		length++;
		n *= -1;
	}
	while ((n /= 10) > 0)
		length++;
	return (length + 1);
}

char			*ft_itoa(int n)
{
	char	*ptr;
	int		nb;

	nb = ft_length(n);
	if (nb + 1 == 0 || !(ptr = (char *)malloc(sizeof(*ptr) * (nb + 1))))
		return (NULL);
	ptr[nb] = '\0';
	while ((--nb > 1 && n < 0) || (nb >= 0 && n >= 0))
	{
		ptr[nb] = n >= 0 ? n % 10 + '0' : -(n % 10) + '0';
		n /= 10;
	}
	if (n < 0)
	{
		ptr[nb--] = -(n % 10) + '0';
		ptr[nb] = '-';
	}
	return (ptr);
}
