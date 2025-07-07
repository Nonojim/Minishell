/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:58:41 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/07 15:35:52 by npederen         ###   ########.fr       */
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
		add_code_error(&ctx->env, 1);
	}
	else if (pid == 0)
		exit(execute_node(node->left, token, line, ctx));
	return (subshell_status(ctx, pid));
}

int	subshell_status(t_ctx *ctx, pid_t pid)
{
	int	status;
	int	code_error;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		code_error = 128 + WTERMSIG(status);
	else if (WIFEXITED(status))
		code_error = WEXITSTATUS(status);
	else
		code_error = 1;
	add_code_error(&ctx->env, code_error);
	return (code_error);
}
