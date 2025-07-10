/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:58:41 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/10 11:47:37 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	execute_subshell_node(t_treenode *node, char *line, t_ctx *ctx)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		ctx->exit_code = 1;
	}
	else if (pid == 0)
	{
		int	exit_code = execute_node(node->left, line, ctx);
		free_treenode(node);
		free_env_list(ctx->env);
		exit(exit_code);
	}
	return (subshell_status(ctx, pid));
}

int	subshell_status(t_ctx *ctx, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		ctx->exit_code = 128 + WTERMSIG(status);
	else if (WIFEXITED(status))
		ctx->exit_code = WEXITSTATUS(status);
	else
		ctx->exit_code = 1;
	return (ctx->exit_code);
}
