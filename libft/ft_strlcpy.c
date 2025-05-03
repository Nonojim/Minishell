/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:31:59 by npederen          #+#    #+#             */
/*   Updated: 2024/11/26 19:34:14 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (src[i])
		i++;
	if (size == 0)
		return (i);
	if ((i + 1 < size))
		ft_memcpy(dst, src, (i + 1));
	else if (size != 0)
	{
		ft_memcpy(dst, src, (size - 1));
		dst[size - 1] = 0;
	}
	return (i);
}

/*#include <stdio.h>
#include <string.h>
int	main(void)
{
	char	src[] = "testet";
	char	dst[] ="test";
	
	size_t n = 4;
	printf("%zu et %s\n", ft_strlcpy(dst, src, n), dst);
	//printf("%zu et %s\n", strlcpy(dst, src, n), dst);
	return (0);
}*/