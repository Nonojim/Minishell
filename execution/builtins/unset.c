/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 23:06:58 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/30 11:35:12 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_unset(t_treenode *node)
{
	int		i;

	i = 1;
	while (node->argv[i])
	{
		if (unset_head_list(node, node->argv[i]))
		{
			i++;
			continue ;
		}
		unset_list(node, node->argv[i]);
		i++;
	}
	return (0);
}

int	unset_head_list(t_treenode *node, char *key)
{
	t_env	*tmp;

	tmp = node->env;
	if (tmp && ft_strcmp(tmp->key, key) == 0)
	{
		node->env = node->env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		return (1);
	}
	return (0);
}

void	unset_list(t_treenode *node, char *key)
{
	t_env	*tmp2;
	t_env	*tmp;

	tmp2 = node->env;
	while (tmp2 && tmp2->next)
	{
		if (ft_strcmp(tmp2->next->key, key) == 0)
		{
			tmp = tmp2->next;
			tmp2->next = tmp2->next->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			break ;
		}
		tmp2 = tmp2->next;
	}
}
