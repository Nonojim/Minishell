/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 20:32:24 by npederen          #+#    #+#             */
/*   Updated: 2024/11/26 14:26:14 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(char	const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	count_words(char const *s, char c)
{
	int	compteur;
	int	boule;

	compteur = 0;
	boule = 0;
	while (*s)
	{
		if (!(*s == c) && !boule)
		{
			compteur++;
			boule = 1;
		}
		else if (*s == c)
			boule = 0;
		s++;
	}
	return (compteur);
}

static char	*alloc_word(char const*s, char c)
{
	int		size;
	int		i;
	char	*word;

	i = 0;
	size = ft_len(s, c);
	word = (char *)malloc(sizeof(char) * (size + 1));
	if (!word)
		return (NULL);
	while (i < size)
	{
		word[i] = s[i];
		i++;
	}
	word[size] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		size;
	char	**tab;

	i = 0;
	size = count_words(s, c);
	tab = (char **)malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			tab[i] = alloc_word(s, c);
			i++;
		}
		while (*s && *s != c)
			s++;
	}
	tab[size] = NULL;
	return (tab);
}

/*#include <stdio.h>

int	main(void)
{
	char	str[] = "  ceci est un test  ";
	char	**tab;
	int i = 0;

	tab = ft_split(str, 'c');
	while (tab[i])	
	{
		printf("%s\n",tab[i]);
		i++;
	}
	//printf("%s\n", *ft_split(tab[0], ""));
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab[i]);
	free(tab);

	return (0);
}*/