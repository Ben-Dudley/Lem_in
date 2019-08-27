/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 20:15:49 by bdudley           #+#    #+#             */
/*   Updated: 2019/02/22 18:35:52 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	int i;
	int j;

	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack != '\0' && n > 0)
	{
		j = 0;
		i = 0;
		while (n-- > 0 && haystack[i++] == needle[j] && needle[j] != '\0')
			j++;
		if (needle[j] == '\0')
			return ((char *)haystack);
		n += j;
		haystack++;
	}
	if (*haystack == '\0' && *needle == '\0')
		return ((char *)haystack);
	return (NULL);
}
