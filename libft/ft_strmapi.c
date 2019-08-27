/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 16:23:30 by bdudley           #+#    #+#             */
/*   Updated: 2019/02/22 16:42:33 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		i;

	i = -1;
	if (s == NULL || (str = ft_strdup(s)) == NULL)
		return (NULL);
	while (s[++i] != '\0')
		str[i] = f(i, s[i]);
	return (str);
}
