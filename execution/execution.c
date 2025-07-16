/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:55:01 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/16 20:06:07 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*
	* Code erreur pour la var $? 
	* (Convention Posix & Bash)
	* Valeur comprise entre 0 et 255.
	* 0 = Succés 
	* 1 = Erreur général
	* 2 = Mauvais usage commande, erreur syntaxe
	* 126 = Command trouvé mais non exe
	* 127 = Command not found
	* 128 = Mauvais usage de exit (ex: exit -1, exit avec trop d'arguments)
	* 130 = Arret avec Ctrl+C
	* 131 = Arret avec Ctrl+\
*/

void	execute_tree(t_treenode *tree, char *line, t_ctx	*ctx)
{
	ctx->exit_code = execute_node(tree, line, ctx);
}

int	execute_node(t_treenode *node, char *line, t_ctx *ctx)
{
	if (!node)
		return (1);
	if (node->type == WORD || node->type == PIPE)
		return (execute_node_simple(node, line, ctx));
	else if (node->type == LOGICAL_AND || node->type == LOGICAL_OR
		|| node->type == SEMICOLON)
		return (execute_node_logical(node, line, ctx));
	else if (node->type == HERE_DOCUMENT
		|| node->type == INPUT_REDIRECTION
		|| node->type == OUTPUT_REDIRECTION
		|| node->type == APPEND_OUTPUT_REDIRECTION
		|| node->type == SUBSHELL)
		return (execute_node_redir(node, line, ctx));
	else
		return (1);
}

int	execute_node_simple(t_treenode *node, char *line, t_ctx *ctx)
{
	if (node->type == WORD)
		return (execute_simple_command(node, line, ctx));
	else if (node->type == PIPE)
		return (execute_pipeline(node, line, ctx));
	return (1);
}

int	execute_node_logical(t_treenode *node, char *line, t_ctx *ctx)
{
	if (node->type == LOGICAL_AND)
	{
		if (execute_node(node->left, line, ctx) == 0)
		{
			ctx->exit_code = execute_node(node->right, line, ctx);
			return(ctx->exit_code);
		}
	}
	else if (node->type == LOGICAL_OR)
	{
		if (execute_node(node->left, line, ctx) != 0)
			ctx->exit_code = execute_node(node->right, line, ctx);
		return (ctx->exit_code);
	}
	else if (node->type == SEMICOLON)
	{
		execute_node(node->left, line, ctx);
		ctx->exit_code = execute_node(node->right, line, ctx);
		return (ctx->exit_code);
	}
	ctx->exit_code = 1;
	return (ctx->exit_code);
}

int	execute_node_redir(t_treenode *node, char *line, t_ctx *ctx)
{
	if (node->type == HERE_DOCUMENT)
	{
		expanse_ast(node, ctx);
		return (execute_heredoc_node(node, line, ctx));
	}
	else if (node->type == INPUT_REDIRECTION
		|| node->type == OUTPUT_REDIRECTION
		|| node->type == APPEND_OUTPUT_REDIRECTION)
		return (execute_redirection_chain(node, line, ctx));
	else if (node->type == SUBSHELL)
		return (execute_subshell_node(node, line, ctx));
	return (1);
}
