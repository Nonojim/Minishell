/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:01:33 by npederen          #+#    #+#             */
/*   Updated: 2024/11/07 17:22:39 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

/*#include <stdio.h>
#include <string.h>
int	main(void)
{
	char str[] = "test";
	char strT[] = "test";

	ft_memset(str, 'k', 4);
	memset(strT, 'k', 4);
	printf("%s\n", str);
	printf("temoin :%s", strT);
	return (0);
}*/