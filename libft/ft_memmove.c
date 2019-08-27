/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 13:49:37 by bdudley           #+#    #+#             */
/*   Updated: 2019/02/22 12:38:31 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*cdst;
	unsigned char	*csrc;
	int				i;

	i = 0;
	cdst = (unsigned char *)dst;
	csrc = (unsigned char *)src;
	if (cdst > csrc)
	{
		i = len;
		while (--i >= 0)
		{
			cdst[i] = csrc[i];
		}
	}
	else if (cdst != csrc)
	{
		i = -1;
		while ((size_t)(++i) < len)
		{
			cdst[i] = csrc[i];
		}
	}
	return (dst);
}
