/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:18:28 by npederen          #+#    #+#             */
/*   Updated: 2024/11/19 18:18:28 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	size_t	size;
	size_t	i;

	i = 0;
	size = ft_strlen(s);
	dest = malloc(sizeof(char) * size + 1);
	if (!dest)
		return (NULL);
	while (i < size)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/*#include <stdio.h>
int	main(void)
{
	const char * original = "The original string.";
    char * copy = ft_strdup( original );
	printf("%s\n", copy);
	return (0);
}*/