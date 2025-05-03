/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:46:03 by npederen          #+#    #+#             */
/*   Updated: 2024/11/07 17:23:04 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
			return ((void *) &str[i]);
		i++;
	}
	return (NULL);
}

/*#include <stdio.h>
int	main(void)
{
	char	data[] = {10, 20, 30, 40, 50};
	const unsigned int	size = 4;
	void 	*found = ft_memchr(data, 50, size);
	printf("resultat %s\n",( found != NULL ? "yep" : "nop" ) );
	return (0);
}
*/