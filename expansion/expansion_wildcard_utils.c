/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_wildcard_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 11:29:43 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/12 11:49:12 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

void	free_wildcard(t_wildcard *psm, char **result, t_treenode *node)
{
	if (!result)
	{
		free(psm->prefix);
		free_split(psm->middle);
		free(psm->suffix);
		free(psm);
	}
	else
	{
		free_split(node->argv);
		free(result);
		free(psm->prefix);
		free(psm->suffix);
		if (psm->middle)
			free_split(psm->middle);
		free(psm);
	}
}

char	**add_array(char **result, char *file)
{
	int		i = 0;
	char	**new;

	while (result && result[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (result && result[i])
	{
		new[i] = result[i];
		i++;
	}
	new[i] = ft_strdup(file);
	new[i + 1] = NULL;
	free(result);
	//printf("ajout : %s\n", file);
	return (new);
}

int	count_middle_wildcard(char *str)
{
	int	i;
	int	middle_wildcard;

	i = 0;
	middle_wildcard = 0;
	while (str[i])
	{
		if (str[i] && str[i] == '*')
		{
			while (str[i] && str[i] == '*')
				i++;
			if (str[i] && str[i] != '*')
			{
				while (str[i] && str[i] != '*')
					i++;
				if (str[i] && str[i] == '*')
					middle_wildcard++;
			}
		}
		else
			i++;
	}
	return (middle_wildcard);
}
