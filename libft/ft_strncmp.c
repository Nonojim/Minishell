/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:59:02 by npederen          #+#    #+#             */
/*   Updated: 2024/11/26 19:34:36 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	n -= 1;
	while (((unsigned char)s1[i] || (unsigned char)s2[i]) && n > i)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/*#include <stdio.h>
#include <string.h>
int	main(void)
{
	char	*test1;
	char	*test2;

	test1 = "1234";
	test2 = "1235";

	printf("resultat : |%d|", strncmp(test1, test2, 3));
	printf(" || resultat strncmp : |%d|", ft_strncmp(test1, test2, 3));
}*/