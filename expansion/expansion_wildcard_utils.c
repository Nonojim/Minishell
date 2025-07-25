/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_wildcard_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 11:29:43 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/25 18:58:48 by lduflot          ###   ########.fr       */
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
	int		i;
	char	**new;

	i = 0;
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
	return (new);
}

void	sort_argv(char **array)
{
	int		i;
	int		a;
	int		b;
	char	*tmp;

	if (!array)
		return ;
	i = 0;
	while (array[i] && array[i + 1])
	{
		a = ft_tolower(array[i][0]);
		b = ft_tolower(array[i + 1][0]);
		if (a > b || (a == b && ft_strcmp(array[i], array[i + 1]) > 0))
		{
			tmp = array[i];
			array[i] = array[i + 1];
			array[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
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

void	free_expand_variable(char *tmp, char *expanse, char *new_str)
{
	if (tmp)
		free(tmp);
	if (expanse)
		free(expanse);
	if (new_str)
		free(new_str);
}
