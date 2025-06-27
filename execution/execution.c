/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:55:01 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/26 16:59:27 by lduflot          ###   ########.fr       */
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

int execute_node(t_treenode *node, t_token *token, char *line)
{
	if (!node)
		return (1);
	if (node->type == WORD)
		return (execute_simple_command(node, token, line));
	else if (node->type == PIPE)
		return (execute_pipeline(node, token, line));
	else if (node->type == LOGICAL_AND)
	{
		if (execute_node(node->left, token, line) == 0)
			return (execute_node(node->right, token, line));
		return (1);
	}
	else if (node->type == LOGICAL_OR)
	{
		if (execute_node(node->left, token, line) == 0)
			return (0);
		return (execute_node(node->right, token, line));
	}
	else if (node->type == SEMICOLON)
	{
		execute_node(node->left, token, line);
		return (execute_node(node->right, token, line));
	}
	else if (node->type == HERE_DOCUMENT)
		return (execute_heredoc_node(node, token, line));
	else if (node->type == INPUT_REDIRECTION || node->type == OUTPUT_REDIRECTION || node->type == APPEND_OUTPUT_REDIRECTION)
		return (execute_redirection_chain(node, token, line));
	else if (node->type == SUBSHELL)
		return (execute_subshell_node(node, token, line));
	else
	{
		printf("unknown node type %d", node->type);
		return(1);
	}
}

void execute_tree(t_treenode *tree, t_token *token, char *line)
{
	int code_error;

	code_error = execute_node(tree, token, line);
	tree->env = add_code_error(tree->env, code_error);
}
