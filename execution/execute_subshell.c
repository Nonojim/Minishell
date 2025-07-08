/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:58:41 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/08 02:14:04 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	execute_subshell_node(t_treenode *node, t_token *token, char *line, t_ctx *ctx)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		ctx->exit_code = 1;
	}
	else if (pid == 0)
		exit(execute_node(node->left, token, line, ctx));
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
