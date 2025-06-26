/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:55:01 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/26 07:47:54 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	execute_node(t_treenode *node)
{
	if (!node)
		return (1);
	//printf("type node: %d, str: %s\n", node->type, node->str);
	if (node->type == WORD) //OK
		return(execute_simple_command(node));
	else if (node->type == PIPE) // OK
		return (execute_pipeline(node));
	else if (node->type == LOGICAL_AND) //OK
	{
		if (execute_node(node->left) == 0)
			return (execute_node(node->right));
		return (1);
	}
	else if (node->type == LOGICAL_OR) //OK
	{
		if  (execute_node(node->left) == 0)
			return (0);
		return (execute_node(node->right));
	}
	else if (node->type == SEMICOLON) //OK
	{
		execute_node(node->left);
		return (execute_node(node->right));
	}
	else if (node->type == HERE_DOCUMENT) // OK
		return (execute_heredoc_node(node));
	else if (node->type == INPUT_REDIRECTION || node->type == OUTPUT_REDIRECTION || node->type == APPEND_OUTPUT_REDIRECTION) //OK
		return (execute_redirection_chain(node));
	else if (node->type == SUBSHELL) //OK
		return (execute_subshell_node(node));
	else
	{
		printf("unknown node type %d", node->type);
		return(1);
	}
}

void	execute_tree(t_treenode *tree)
{
	execute_node(tree);
}
