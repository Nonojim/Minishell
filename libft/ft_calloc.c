/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:47:29 by npederen          #+#    #+#             */
/*   Updated: 2024/11/19 17:47:29 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*str;

	str = malloc(size * nmemb);
	if (!str)
		return (NULL);
	ft_memset(str, 0, size * nmemb);
	return (str);
}

/*#include <stdio.h>          
int main() {
	
	int i;
	int *pointer = (int *) ft_calloc( 5, sizeof(int) );

	i = 0;
	while (i < 5) {
		printf( "%d ", pointer[i] );
		i++;
	}
	free(pointer);
	return 0;
}*/