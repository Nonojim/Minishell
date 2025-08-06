/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:00:05 by lduflot           #+#    #+#             */
/*   Updated: 2025/08/06 11:03:51 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	execute_heredoc_node(t_treenode *node, char *line, t_ctx *ctx)
{
	int			pipefd[2];
	int			pid;
	int			exit_code;
	t_treenode	*last_hd;
	t_treenode	*cmd;

	if (found_last_heredoc_and_cmd(node, &last_hd, &cmd, ctx) == 1)
		return (ctx->exit_code);
	if (pipe(pipefd) == -1)
		return (perror("pipe"), ctx->exit_code = 1);
	write(pipefd[1], last_hd->right->str, ft_strlen(last_hd->right->str));
	close(pipefd[1]);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), ctx->exit_code = 1);
	if (pid == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		exit_code = execute_node(cmd, line, ctx);
		free_hd(node, ctx, line);
		exit(exit_code);
	}
	close(pipefd[0]);
	return (heredoc_status(ctx, pid, node, line));
}

int	found_last_heredoc_and_cmd(t_treenode *node, \
		t_treenode **last_hd, t_treenode **cmd, t_ctx *ctx)
{
	if (!node)
		return (ctx->exit_code = 0);
	new_argv_cmd(node);
	*last_hd = node;
	*cmd = node;
	while (*last_hd && (*last_hd)->type == HERE_DOCUMENT
		&& (*last_hd)->right && (*last_hd)->right->type == HERE_DOCUMENT)
		*last_hd = (*last_hd)->right;
	while (*cmd && (*cmd)->type == HERE_DOCUMENT)
		*cmd = (*cmd)->left;
	if (!*last_hd || !(*last_hd)->right || !(*last_hd)->right->str || !*cmd)
		return (ctx->exit_code = 1);
	return (0);
}

void	free_hd(t_treenode *node, t_ctx *ctx, char *line)
{
	if (node)
		free_treenode(node);
	if (ctx)
		free_env_list(ctx->env);
	if (line)
		free_then_setnull((void **)&line);
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
		ctx->exit_code = 130;
	}
	else if (WIFEXITED(status))
		ctx->exit_code = WEXITSTATUS(status);
	else
		ctx->exit_code = 1;
	return (ctx->exit_code);
}
