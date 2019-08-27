/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 21:52:44 by bdudley           #+#    #+#             */
/*   Updated: 2018/12/14 21:38:15 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t len;

	len = 0;
	if ((int)size - (int)ft_strlen(dst) - 1 >= 0)
	{
		len = ft_strlen(src) + ft_strlen(dst);
		dst = ft_strncat(dst, src, (int)size - (int)ft_strlen(dst) - 1);
		return (len);
	}
	else
		return (ft_strlen(src) + size);
}
