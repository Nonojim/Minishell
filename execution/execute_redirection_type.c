/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection_type.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:36:49 by lduflot           #+#    #+#             */
/*   Updated: 2025/08/08 16:37:52 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*Parcours les node de redirs de manière récursive de gauche à droite*/
int	apply_redirections(t_treenode *node, char *line, t_ctx *ctx)
{
	int	status;

	status = 0;
	if (!node)
		return (1);
	if (node->left)
		status = apply_redirections(node->left, line, ctx);
	if (status != 0)
		return (status);
	if (node->type == INPUT_REDIRECTION)
		return (redir_input(node, ctx));
	else if (node->type == HERE_DOCUMENT)
		return (redir_heredoc(node, ctx));
	else if (node->type == OUTPUT_REDIRECTION)
		return (redir_output(node, ctx));
	else if (node->type == APPEND_OUTPUT_REDIRECTION)
		return (redir_append(node, ctx));
	return (0);
}

int	redir_heredoc(t_treenode *node, t_ctx *ctx)
{
	int	pipefd[2];
	int	len;

	if (!node || !node->right || !node->right->str)
		return (ctx->exit_code = 1);
	if (pipe(pipefd) == -1)
		return (perror("pipe"), ctx->exit_code = 1);
	len = ft_strlen(node->right->str);
	if (write(pipefd[1], node->right->str, len) != len)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (perror("write"), ctx->exit_code = 1);
	}
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		close(pipefd[0]);
		return (perror("dup2"), ctx->exit_code = 1);
	}
	close(pipefd[0]);
	return (0);
}

/* Gestion de : <
Ouvre le fichier en lecture seul et le met à l'entrée standard*/
int	redir_input(t_treenode *node, t_ctx *ctx)
{
	int	fd;

	if (!node->right || !node->right->str)
		return (1);
	fd = open(node->right->str, O_RDONLY);
	if (fd < 0)
	{
		ft_fprintf(2, "minishell: %s: %s\n", node->right->str, strerror(errno));
		ctx->exit_code = 1;
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

/*Gestion : >
Ouvre ou crée le file en écriture et le met à la sortie standard
Supprime son contenu avec O_TRUNC*/
int	redir_output(t_treenode *node, t_ctx *ctx)
{
	int	fd;

	if (!node->right || !node->right->str)
		return (1);
	fd = open(node->right->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_fprintf(2, "minishell: %s: %s\n", node->right->str, strerror(errno));
		ctx->exit_code = 1;
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

/* Gestion de : >>
Ouvre ou crée le file et le met à la sortie standard
Ajoute du contenue à la fin avec O_APPEND*/
int	redir_append(t_treenode *node, t_ctx *ctx)
{
	int	fd;

	if (!node->right || !node->right->str)
		return (1);
	fd = open(node->right->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_fprintf(2, "minishell: %s: %s\n", node->right->str, strerror(errno));
		ctx->exit_code = 1;
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}
