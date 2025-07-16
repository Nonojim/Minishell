/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_wildcard_match.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 19:23:13 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/13 19:28:42 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

//verif que str commence par le prefix
int	match_prefix(char *str, char *prefix)
{
	int	match;
	int	len_prefix;

	len_prefix = ft_strlen(prefix);
	match = ft_strncmp(str, prefix, len_prefix);
	if (match == 0)
		return (1);
	return (0);
}

int	match_middle(char *str, char **middle)
{
	int	match;
	int	len_str;
	int	i;

	i = 0;
	while (middle[i])
	{
		len_str = ft_strlen(str);
		match = ft_strnstr_for_wildcard(str, middle, len_str);
		if (match == 0)
			return (1);
		i++;
	}
	return (0);
}

//3eme while = permet de chercher/trouver dans l'ordre des middles
int	ft_strnstr_for_wildcard(char *str,	char **middle, int len_str)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (middle[j])
	{
		while (i < len_str)
		{
			k = 0;
			while (str[i + k] && middle[j][k] && str[i + k] == middle[j][k])
				k++;
			if (middle[j][k] == '\0')
			{
				i = i + k;
				break ;
			}
			i++;
		}
		if (i >= len_str)
			return (1);
		j++;
	}
	return (0);
}

//verif que str finit par le suffix
int	match_suffix(char *str, char *suffix)
{
	int	len_str;
	int	len_suffix;
	int	match;

	len_str = ft_strlen(str);
	len_suffix = ft_strlen(suffix);
	match = ft_strcmp(str + len_str - len_suffix, suffix);
	if (match == 0)
		return (1);
	return (0);
}
