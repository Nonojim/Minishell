/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:58:07 by npederen          #+#    #+#             */
/*   Updated: 2024/11/26 15:19:10 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstlen;
	size_t	srclen;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (dstlen >= size)
		dstlen = size;
	if (dstlen == size)
		return (size + srclen);
	if (srclen < size - dstlen)
		ft_memcpy(dst + dstlen, src, srclen + 1);
	else
	{
		ft_memcpy(dst + dstlen, src, size - dstlen - 1);
		dst[size - 1] = '\0';
	}
	return (dstlen + srclen);
}

/*#include <string.h>
#include <stdio.h>
int	main (void)
{
	char	dest[20] = "je taime ";
	char	src [] = "pas";
	size_t	size = sizeof(dest);
	size_t	resultat;

	resultat = ft_strlcat(dest, src, size);
	printf("dest = %s\n", dest);
	printf("resultat = %zu", resultat);
	
}*/