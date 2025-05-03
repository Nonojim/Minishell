/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:42:56 by npederen          #+#    #+#             */
/*   Updated: 2024/11/26 18:41:49 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

/*#include <stdio.h>
#include <string.h>
int	main(void)
{
	const char str[] = "teste";
	int c = 1024;

	printf("[%p]\n", ft_strchr(str, c));
	printf("temoin : [%p]", strchr(str, c));
	return (0);
}
*/