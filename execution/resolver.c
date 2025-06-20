/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:43:16 by npederen          #+#    #+#             */
/*   Updated: 2025/06/20 18:47:18 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_node(t_treenode *node)
{
	if (!node)
		return (1);
	if (node->type == WORD)
		return(execute_simple_command(node));
	else if (node->type == PIPE)
		return (execute_pipeline(node));
	else if (node->type == LOGICAL_AND)
	{
		if  (execute_node(node->left) == 0)
			return (execute_node(node->right));
		return (1);
	}
	else if (node->type == LOGICAL_OR)
	{
		if  (execute_node(node->left) == 0)
			return (0);
		return (execute_node(node->right));
	}
	else if (node->type == SEMICOLON)
	{
		execute_node(node->left);
		return (execute_node(node->right));
	}
	else if (node->type == HERE_DOCUMENT)
		return (execute_heredoc_node(node));
	else if (node->type == APPEND_OUTPUT_REDIRECTION)
		return (execute_append_node(node));
	else if (node->type == INPUT_REDIRECTION)
		return (execute_input_node(node));
	else if (node->type == OUTPUT_REDIRECTION)
		return (execute_output_node(node));
	else if (node->type == SUBSHELL)
		return (execute_subshell_node(node));
	else
		return(1, printf("unknown node type %d", node->type));
}

void	execute_tree(t_treenode *tree)
{
	execute_node(tree);
}