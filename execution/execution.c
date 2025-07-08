/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:55:01 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/08 02:14:33 by lduflot          ###   ########.fr       */
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

void	execute_tree(t_treenode *tree, t_token *token, char *line, t_ctx	*ctx)
{

	ctx->exit_code = execute_node(tree, token, line, ctx);
}

int	execute_node(t_treenode *node, t_token *token, char *line, t_ctx *ctx)
{
	if (!node)
		return (1);
	if (node->type == WORD || node->type == PIPE)
		return (execute_node_simple(node, token, line, ctx));
	else if (node->type == LOGICAL_AND || node->type == LOGICAL_OR
		|| node->type == SEMICOLON)
		return (execute_node_logical(node, token, line, ctx));
	else if (node->type == HERE_DOCUMENT
		|| node->type == INPUT_REDIRECTION
		|| node->type == OUTPUT_REDIRECTION
		|| node->type == APPEND_OUTPUT_REDIRECTION
		|| node->type == SUBSHELL)
		return (execute_node_redir(node, token, line, ctx));
	else
	{
		printf("unknown node type %d\n", node->type);
		return (1);
	}
}

int	execute_node_simple(t_treenode *node, t_token *token, char *line, t_ctx *ctx)
{
	if (node->type == WORD)
		return (execute_simple_command(node, token, line, ctx));
	else if (node->type == PIPE)
		return (execute_pipeline(node, token, line, ctx));
	return (1);
}

int	execute_node_logical(t_treenode *node, t_token *token, char *line, t_ctx *ctx)
{
	if (node->type == LOGICAL_AND)
	{
		if (execute_node(node->left, token, line, ctx) == 0)
			return (execute_node(node->right, token, line, ctx));
		return (1);
	}
	else if (node->type == LOGICAL_OR)
	{
		if (execute_node(node->left, token, line, ctx) == 0)
			return (0);
		return (execute_node(node->right, token, line, ctx));
	}
	else if (node->type == SEMICOLON)
	{
		execute_node(node->left, token, line, ctx);
		return (execute_node(node->right, token, line, ctx));
	}
	return (1);
}

int	execute_node_redir(t_treenode *node, t_token *token, char *line, t_ctx *ctx)
{
	if (node->type == HERE_DOCUMENT)
	{
		expanse_ast(node, ctx);
		return (execute_heredoc_node(node, token, line, ctx));
	}
	else if (node->type == INPUT_REDIRECTION
		|| node->type == OUTPUT_REDIRECTION
		|| node->type == APPEND_OUTPUT_REDIRECTION)
		return (execute_redirection_chain(node, token, line, ctx));
	else if (node->type == SUBSHELL)
		return (execute_subshell_node(node, token, line, ctx));
	return (1);
}
