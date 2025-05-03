/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:49:42 by npederen          #+#    #+#             */
/*   Updated: 2024/11/26 19:40:20 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	if ((unsigned char)c == '\0')
		return ((char *)&s[i]);
	while (i >= 0)
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}

/*#include <stdio.h>
#include <string.h>
int	main(void)
{
	const char str[] = "teste";
	//const char test[] = "teste";
	int c = 1024;
	int r = '\0';

	printf("[%p]\n", ft_strrchr(str, c));
	printf("temoin [%p]", strrchr(str, r));
	return (0);
}*/