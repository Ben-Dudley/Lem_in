/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 20:36:44 by bdudley           #+#    #+#             */
/*   Updated: 2018/12/06 21:34:10 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t i;

	i = 0;
	while (*src != '\0' && i < len)
	{
		dst[i] = *src;
		src++;
		i++;
	}
	while (i < len)
		dst[i++] = '\0';
	return (dst);
}
