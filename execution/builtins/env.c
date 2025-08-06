/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:49:03 by npederen          #+#    #+#             */
/*   Updated: 2025/08/02 13:50:05 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_env(t_treenode *node, t_ctx *ctx)
{
	t_env	*tmp;

	if (node->argv[1] != NULL)
	{
		ft_fprintf(2, "minishell: env: ‘%s’: No such file or directory\n", \
node->argv[1]);
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
