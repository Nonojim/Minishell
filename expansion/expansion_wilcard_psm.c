/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_wilcard_psm.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:22:58 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/23 16:28:18 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

void	create_prefix_middle_suffix(char *str, t_wildcard *psm)
{
	int	i;
	int	middle_wildcard;

	i = 0;
	middle_wildcard = count_middle_wildcard(str);
	allocation_psm_middle(psm, middle_wildcard);
	i = create_prefix(str, psm);
	create_psm_middle_suffix(str, psm, i);
}

int	create_prefix(char *str, t_wildcard *psm)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	if (str[i] && str[i] != '*')
	{
		start = 0;
		while (str[i] && str[i] != '*')
			i++;
		psm->prefix = ft_substr(str, start, i - start);
	}
	return (i);
}

void	allocation_psm_middle(t_wildcard *psm, int middle_wildcard)
{
	if (middle_wildcard > 0)
	{
		psm->middle = malloc(sizeof(char *) * (middle_wildcard + 1));
		if (!psm->middle)
			return ;
	}
	else
		psm->middle = NULL;
}

void	create_psm_middle_suffix(char *str, t_wildcard *psm, int i)
{
	int	j;
	int	start;

	j = 0;
	start = 0;
	while (str[i])
	{
		while (str[i] == '*')
			i++;
		start = i;
		while (str[i] && str[i] != '*')
			i++;
		if (str[i] == '*' && i > start)
		{
			psm->middle[j] = ft_substr(str, start, i - start);
			j++;
		}
		else if (!str[i] && i > start)
			psm->suffix = ft_substr(str, start, i - start);
	}
	if (psm->middle)
		psm->middle[j] = NULL;
}
