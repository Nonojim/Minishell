/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:00:05 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/09 13:25:49 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	heredoc_status(t_ctx *ctx, pid_t pid);

int	execute_heredoc_node(t_treenode *node, char *line, t_ctx *ctx)
{
	int	pipefd[2];
	int	pid;

	pipe(pipefd);
	write(pipefd[1], node->right->str, ft_strlen(node->right->str));
	close(pipefd[1]);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		ctx->exit_code = 1;
		return (1);
	}
	if (pid == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		exit(execute_node(node->left, line, ctx));
	}
	close(pipefd[0]);
	return (heredoc_status(ctx, pid));
}

int	heredoc_status(t_ctx *ctx, pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		ctx->exit_code = 1;
		return (1);
	}
	if (WIFSIGNALED(status))
		ctx->exit_code = 128 + WTERMSIG(status);
	else if (WIFEXITED(status))
		ctx->exit_code = WEXITSTATUS(status);
	else
		ctx->exit_code = 1;
	return (ctx->exit_code);
}
