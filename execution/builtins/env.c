/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:49:03 by npederen          #+#    #+#             */
/*   Updated: 2025/07/16 20:10:47 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_env(t_treenode *node, t_ctx *ctx)
{
	t_env	*tmp;

	if (node->argv[1] != NULL)
	{
		ft_fprintf(2, "minishell: env: ‘%s’: No such file or directory\n", node->argv[1]);
		ctx->exit_code = 127;
		return (127);
	}
	tmp = ctx->env;
	while (tmp)
	{
		if (tmp->value && ft_strcmp(tmp->key, "?") != 0)
			ft_fprintf(1, "%s=%s\n", tmp->key, tmp->value);
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
