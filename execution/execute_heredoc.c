/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:00:05 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/12 20:28:16 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"


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
		int exit_code = execute_node(node->left, line, ctx);
		free_treenode(node);
		free_env_list(ctx->env);
		free(line);
		exit(exit_code);
	}
	close(pipefd[0]);
	return (heredoc_status(ctx, pid, node, line));
}

int	heredoc_status(t_ctx *ctx, pid_t pid, t_treenode *node, char *line)
{
	int	status;
	(void)line;
	(void)node;
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		ctx->exit_code = 1;
		return (1);
	}
	if (WIFSIGNALED(status))
	{
		printf("CTRL+C");
	//	free_treenode(node);
//		free_env_list(ctx->env);
	//	free(line);
		ctx->exit_code = 130;
	}
	else if (WIFEXITED(status))
		ctx->exit_code = WEXITSTATUS(status);
	else
		ctx->exit_code = 1;
	return (ctx->exit_code);
}
