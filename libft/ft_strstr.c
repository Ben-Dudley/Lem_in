/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 18:36:46 by bdudley           #+#    #+#             */
/*   Updated: 2018/11/30 21:51:23 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int i;
	int j;

	while (*haystack != '\0')
	{
		j = 0;
		i = 0;
		while (haystack[i++] == needle[j] && needle[j] != '\0')
			j++;
		if (needle[j] == '\0')
			return ((char *)haystack);
		haystack++;
	}
	if (*haystack == '\0' && *needle == '\0')
		return ((char *)haystack);
	return (NULL);
}
