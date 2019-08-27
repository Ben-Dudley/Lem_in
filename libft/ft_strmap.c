/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 16:12:17 by bdudley           #+#    #+#             */
/*   Updated: 2019/02/22 15:45:05 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*str;
	int		i;

	i = -1;
	if (s == NULL || (str = ft_strdup(s)) == NULL || f == NULL)
		return (NULL);
	while (s[++i] != '\0')
		str[i] = f(s[i]);
	return (str);
}
