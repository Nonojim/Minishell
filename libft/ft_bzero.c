/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:39:02 by npederen          #+#    #+#             */
/*   Updated: 2024/11/07 15:49:21 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = '\0';
		i++;
	}
}

/*#include <stdio.h>
#include <stdlib.h>
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
int	main(void)
{
	char str[] = "abcdefghi";
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(str);
	ft_bzero(str, 4);
	while (i < j)
	{
		printf("%c", str[i]);
		i++;
	}
	return (0);
}*/
