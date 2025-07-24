/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:00:27 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/24 12:04:54 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*Applique toutes les redirs de l'AST,
Exe la cmd, et save les entrées/sortie.*/
int	execute_redirection_chain(t_treenode *node, char *line, t_ctx *ctx)
{
	int			saved_stdin;
	int			saved_stdout;
	int			status;
	t_treenode	*cmd;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	new_argv_cmd(node);
	status = apply_redirections(node, line, ctx);
	if (status != 0)
	{
		ctx->exit_code = 1;
		dup_and_close(saved_stdin, saved_stdout);
		return (1);
	}
	cmd = find_command_node(node);
	if (!cmd || !cmd->argv || !cmd->argv[0])
	{
		dup_and_close(saved_stdin, saved_stdout);
		return (0);
	}
	status = execute_node(cmd, line, ctx);
	dup_and_close(saved_stdin, saved_stdout);
	return (status);
}

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
	else if (node->type == OUTPUT_REDIRECTION)
		return (redir_output(node, ctx));
	else if (node->type == APPEND_OUTPUT_REDIRECTION)
		return (redir_append(node, ctx));
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
