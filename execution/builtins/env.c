/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:49:03 by npederen          #+#    #+#             */
/*   Updated: 2025/07/05 19:01:22 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_env(t_env *env_list)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (tmp->value && ft_strcmp(tmp->key, "?") != 0)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

//void	print_env_reverse(t_env *node)
//{
//	if (!node)
//		return;
//	print_env_reverse(node->next);
//	if (node->value && ft_strcmp(node->key, "?") != 0)
//		printf("%s=%s\n", node->key, node->value);
//}
//
//int	ft_env(t_env *env_list)
//{
//	//env_list = env_list->next;
//	print_env_reverse(env_list);
//	return (0);
//}