/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:44:10 by npederen          #+#    #+#             */
/*   Updated: 2024/11/26 19:13:38 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	if ((size_t)dest >= (size_t)src)
	{
		while (n > 0)
		{
			(((char *)dest)[n - 1] = ((char *)src)[n - 1]);
			n--;
		}
	}
	else
	{
		while (i < n)
		{
			((char *)dest)[i] = ((char *)src)[i];
			i++;
		}
	}
	return (dest);
}

/*#include <stdio.h>
#include <string.h>
int main (void)
{
	//char src[200] = "je taime";
	char srcT[200] = "je taime";
	//char dest[] = "0x 12345 pas";
	//char destT[] = "0x 12345 pas";
	size_t n = 3;
	
	//ft_memmove(src + 3, src, n);
	memmove(srcT + 3, srcT, n);
	//printf("ft_memmove :[%s]\n", src + 3);
	printf("memmove :[%s]", srcT + 3);
	return (0);
}*/