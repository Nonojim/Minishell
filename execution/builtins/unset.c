/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 23:06:58 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/10 11:56:03 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_unset(t_treenode *node, t_ctx *ctx)
{
	int		i;

	i = 1;
	while (node->argv[i])
	{
		if (unset_head_list(ctx, node->argv[i]))
		{
			i++;
			continue ;
		}
		unset_list(ctx, node->argv[i]);
		i++;
	}
	return (0);
}

int	unset_head_list(t_ctx *ctx, char *key)
{
	t_env	*tmp;

	tmp = ctx->env;
	if (tmp && ft_strcmp(tmp->key, key) == 0)
	{
		ctx->env = ctx->env->next;
		free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
		return (1);
	}
	return (0);
}

void	unset_list(t_ctx *ctx, char *key)
{
	t_env	*tmp2;
	t_env	*tmp;

	tmp2 = ctx->env;
	while (tmp2 && tmp2->next)
	{
		if (ft_strcmp(tmp2->next->key, key) == 0)
		{
			tmp = tmp2->next;
			tmp2->next = tmp2->next->next;
			free(tmp->key);
			if (tmp->value)
				free(tmp->value);
			free(tmp);
			break ;
		}
		tmp2 = tmp2->next;
	}
}
