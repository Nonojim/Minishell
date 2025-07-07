/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command_builtins.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:55:53 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/07 13:58:27 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	execute_builtin_command(t_treenode *node, t_token *token, char *line, t_ctx *ctx)
{
	char	*cmd;

	cmd = node->argv[0];
	if (ft_strcmp(cmd, "echo") == 0)
		return (ft_echo(node));
	if (ft_strcmp(cmd, "pwd") == 0)
		return (ft_pwd(ctx));
	if (ft_strcmp(cmd, "cd") == 0)
		return (ft_cd(node, ctx));
	if (ft_strcmp(cmd, "export") == 0)
		return (ft_export(node, ctx));
	if (ft_strcmp(cmd, "unset") == 0)
		return (ft_unset(node, ctx));
	if (ft_strcmp(cmd, "env") == 0)
		return (ft_env(ctx->env));
	if (ft_strcmp(cmd, "exit") == 0)
		return (ft_exit(line, token, node, ctx));
	return (1);
}

int	is_builtin(char *cmd)
{
	return (
		ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}
