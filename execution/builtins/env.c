/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:49:03 by npederen          #+#    #+#             */
/*   Updated: 2025/07/04 12:55:37 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

//int	ft_env(t_env *env_list)
//{
//	t_env	*tmp;
//
//	tmp = env_list;
//	while (tmp)
//	{
//		if (tmp->value)
//			printf("%s=%s\n", tmp->key, tmp->value);
//		tmp = tmp->next;
//	}
//	return (0);
//}
static void	print_env_reverse(t_env *node)
{
	if (!node)
		return;
	print_env_reverse(node->next);
	if (node->value)
		printf("%s=%s\n", node->key, node->value);
}

int	ft_env(t_env *env_list)
{
	print_env_reverse_rec(env_list);
	return (0);
}