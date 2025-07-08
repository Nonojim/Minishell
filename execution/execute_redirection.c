/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:00:27 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/08 14:40:07 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	execute_redirection_chain(t_treenode *node, t_token *token, char *line, t_ctx *ctx)
{
	int	saved_stdin;
	int	saved_stdout;
	int	status;

	status = 1;
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (!node)
	{
		ctx->exit_code = 1;
		return (1);
	}
	if (node->type == INPUT_REDIRECTION)
		status = redir_input(node, token, line, ctx);
	else if (node->type == OUTPUT_REDIRECTION)
		status = redir_output(node, token, line, ctx);
	else if (node->type == APPEND_OUTPUT_REDIRECTION)
		status = redir_append(node, token, line, ctx);
	else
		status = execute_node(node, token, line, ctx);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	ctx->exit_code = status;
	return (ctx->exit_code);
}

int	redir_input(t_treenode *node, t_token *token, char *line, t_ctx *ctx)
{
	int	fd;

	fd = open(node->right->str, O_RDONLY);
	if (fd < 0)
	{
		fprintf(stderr, "minishell: %s: %s\n", node->right->str, strerror(errno));
		ctx->exit_code = 1;
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (execute_redirection_chain(node->left, token, line, ctx));
}

int	redir_output(t_treenode *node, t_token *token, char *line, t_ctx *ctx)
{
	int	fd;

	fd = open(node->right->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		fprintf(stderr, "minishell: %s: %s\n", node->right->str, strerror(errno));
		ctx->exit_code = 1;
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (execute_redirection_chain(node->left, token, line, ctx));
}

int	redir_append(t_treenode *node, t_token *token, char *line, t_ctx *ctx)
{
	int	fd;

	fd = open(node->right->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		fprintf(stderr, "minishell: %s: %s\n", node->right->str, strerror(errno));
		ctx->exit_code = 1;
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (execute_redirection_chain(node->left, token, line, ctx));
}

