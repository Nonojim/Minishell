/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:04:30 by lduflot           #+#    #+#             */
/*   Updated: 2025/08/08 19:37:21 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(t_ctx *ctx, t_treenode *node)
{
	char	*pwd;

	if (check_argv_pwd(node, ctx) == 1)
		return (ctx->exit_code);
	pwd = ft_getenv("PWD", ctx);
	if (!pwd)
	{
		perror("pwd");
		ctx->exit_code = 1;
		return (1);
	}
	ft_fprintf(1, "%s\n", pwd);
	return (0);
}

int	check_argv_pwd(t_treenode *node, t_ctx *ctx)
{
	int	i;

	i = 1;
	while (node->argv[1] && node->argv[1][i])
	{
		if (node->argv[1] && node->argv[1][0] == '-'
		&& node->argv[1][1] == '-' && node->argv[1][2] != '\0')
		{
			ft_fprintf(2, "bash: pwd: --: invalid option\n\
pwd: usage: pwd [-LP]\n");
			ctx->exit_code = 2;
			return (1);
		}
		if (node->argv[1] && node->argv[1][0] == '-'
			&& node->argv[1][i] != 'L' && node->argv[1][i] != 'P'
			&& node->argv[1][1] != '-')
		{
			ft_fprintf(2, "bash: pwd: %c%c: invalid option\n\
pwd: usage: pwd [-LP]\n", node->argv[1][0], node->argv[1][i]);
			ctx->exit_code = 2;
			return (1);
		}
		i++;
	}
	return (0);
}
