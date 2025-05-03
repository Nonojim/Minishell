/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:26:33 by npederen          #+#    #+#             */
/*   Updated: 2024/11/26 17:52:12 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

/*#include <stdio.h>
#include <string.h>
int main (void)
{
	char src[] = "je taime";
	char dest[] = "0x 12345 pas";
	char srcT[] = "je taime";
	char destT[] = "0x 12345 pas";
	size_t n = 8;
	
	ft_memcpy(dest, src, n);
	memcpy(destT, srcT, n);
	printf("ft_memcpy :[%s]\n", dest);
	printf("memcpy :[%s]", destT);
	return (0);
}*/