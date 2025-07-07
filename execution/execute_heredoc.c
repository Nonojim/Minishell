/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:00:05 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/07 15:28:28 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	heredoc_status(t_ctx *ctx, pid_t pid);

int	execute_heredoc_node(t_treenode *node, t_token *token, char *line, t_ctx *ctx)
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
		add_code_error(&ctx->env, 1);
		return (1);
	}
	if (pid == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		exit(execute_node(node->left, token, line, ctx));
	}
	close(pipefd[0]);
	return (heredoc_status(ctx, pid));
}

int	heredoc_status(t_ctx *ctx, pid_t pid)
{
	int	status;
	int	code_error;

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		add_code_error(&ctx->env, 1);
		return (1);
	}
	if (WIFSIGNALED(status))
		code_error = 129 + WTERMSIG(status);
	else if (WIFEXITED(status))
		code_error = 130 + WEXITSTATUS(status);
	else
		code_error = 1;
	add_code_error(&ctx->env, code_error);

	return (code_error);
}
