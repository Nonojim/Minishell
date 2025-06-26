/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 23:06:58 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/26 09:38:32 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_unset(t_treenode *node)
{
	int	i = 1;
	t_env	*tmp;
	t_env	*tmp2;

	while(node->argv[i])
	{
		tmp = node->env;
		if (tmp && ft_strcmp(tmp->key, node->argv[i]) == 0)
		{
			node->env = node->env->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			i++;
			continue;
		}
		tmp2 = node->env;
		while (tmp2 && tmp2->next)
		{
			if (tmp2->next && ft_strcmp(tmp2->next->key, node->argv[i]) == 0)
			{
				tmp = tmp2->next;
				tmp2->next = tmp2->next->next;
				free(tmp->key);
				free(tmp->value);
				free(tmp);
				break;
			}
			tmp2 = tmp2->next;
		}
		i++;
	}
	return (0);
}
