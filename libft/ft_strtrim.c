/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:18:20 by npederen          #+#    #+#             */
/*   Updated: 2024/11/26 14:28:22 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isfromset(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	size;

	if (ft_strlen(s1) == 0)
		return (str = ft_calloc(1, sizeof(char)));
	i = 0;
	j = (ft_strlen(s1) - 1);
	k = 0;
	while (j >= i && isfromset(s1[i], set))
		i++;
	while (j > i && isfromset(s1[j], set))
		j--;
	size = j - (i - 1);
	str = ft_calloc((size + 1), sizeof(char));
	if (!str)
		return (NULL);
	while (k < size)
	{
		str[k] = s1[i + k];
		k++;
	}
	return (str);
}

/*
#include <stdio.h>
//printf("size : %lld\n", size);
int	main(void)
{
	printf("str : [%s]", ft_strtrim("", "aaa"));
	return (0);
}
*/