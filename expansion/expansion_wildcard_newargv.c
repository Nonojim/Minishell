/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_wildcard_newargv.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:01:53 by lduflot           #+#    #+#             */
/*   Updated: 2025/08/06 15:56:59 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

void	create_new_argv(char **result, t_treenode *node,\
											t_wildcard *idx)
{
	char	**new_argv;

	if (!node || !node->argv)
		return ;
	idx->len_argv = len_array(node->argv);
	idx->len_result = len_array(result);
	new_argv = malloc(sizeof(char *) * (idx->len_argv + idx->len_result + 1));
	if (!new_argv)
		return ;
	new_argv = build_new_argv(node, result, idx, new_argv);
	free_wildcard(idx, result, node);
	node->argv = new_argv;
}

char	**build_new_argv(t_treenode *node, char **result, t_wildcard *idx,\
												char **new_argv)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (i < idx->wildcard_index)
	{
		new_argv[i] = ft_strdup(node->argv[i]);
		i++;
	}
	j = 0;
	while (result[j])
	{
		new_argv[i + j] = result[j];
		j++;
	}
	k = idx->wildcard_index + 1;
	while (k < idx->len_argv)
	{
		new_argv[i + j] = ft_strdup(node->argv[k]);
		k++;
		j++;
	}
	new_argv[i + j] = NULL;
	return (new_argv);
}

int	len_array(char **result)
{
	int	i;

	i = 0;
	while (result && result[i])
		i++;
	return (i);
}
