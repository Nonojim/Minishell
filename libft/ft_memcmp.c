/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:34:24 by npederen          #+#    #+#             */
/*   Updated: 2024/11/19 16:34:24 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*mem1;
	unsigned char	*mem2;

	if (n == 0)
		return (0);
	mem1 = (unsigned char *) s1;
	mem2 = (unsigned char *) s2;
	while (0 < n)
	{
		if ((unsigned char)*mem1 != (unsigned char)*mem2)
			return ((unsigned char)*mem1 - (unsigned char)*mem2);
		mem1++;
		mem2++;
		n--;
	}
	return (0);
}

/*#include <stdio.h>
#include <string.h>
int	main(void)
{
	size_t	n;
	char	*test1;
	char	*test2;

	n = 3;
	test1 = "ABCdee";
	test2 = "ABCeee";

	printf("resultat temoin : |%d|", memcmp(test1, test2, n));
	printf(" || resultat ft_memcmp : |%d|", ft_memcmp(test1, test2, n));
}*/