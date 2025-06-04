/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:45:33 by npederen          #+#    #+#             */
/*   Updated: 2025/06/04 23:54:24 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	print_indent(int depth)
{
	while (depth-- > 0)
		printf("  ");
}

void	astreeprint(t_treenode *node, int depth)
{
	if (!node)
		return ;
	print_indent(depth);
	printf("[Type: %i", node->type);
	if (node->str)
		printf(", data: \"%s\"]", node->str);
	printf("\n");
	if (node->left)
	{
		print_indent(depth);
		printf("Left:\n");
		astreeprint(node->left, depth + 1);
	}
	if (node->right)
	{
		print_indent(depth);
		printf("Right:\n");
		astreeprint(node->right, depth + 1);
	}
}

// INIT NODE - ADD NODE - FREE NODE 
t_treenode	*create_treenode(int type, char *str)
{
	t_treenode	*new_node;

	new_node = ft_calloc(1, sizeof(t_treenode));
	if (new_node == NULL)
		return (NULL);
	new_node->type = type;
	new_node->str = str;
	//new_node->argv = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

void	free_treenode(t_treenode *treenode)
{
	if (treenode == NULL)
		return ;
	if (treenode->str)
		free(treenode->str);
	free_treenode(treenode->left);
	free_treenode(treenode->right);
	free(treenode);
}

void	add_node(t_treenode *parent_node, t_treenode *new_child, int dir)
{
	if (parent_node == NULL)
		parent_node = new_child;
	else
	{
		if (dir == 0)
			parent_node->left = new_child;
		else if (dir == 1)
			parent_node->right = new_child;
	}
}

t_treenode	*create_branch_words(t_token **token_list)
{
	t_treenode	*root = NULL;
	t_treenode	*current = NULL;
	t_treenode	*new_node = NULL;

	while (*token_list != NULL
		&& ((*token_list)->type == WORD
	|| (*token_list)->type == EXPANSION
	|| (*token_list)->type == SIMPLE_QUOTE
	|| (*token_list)->type == DOUBLE_QUOTE ))
	{
		new_node = create_treenode((*token_list)->type, (*token_list)->str);
		if (!root)
		{
			root = new_node;
			current = root;
		}
		else
		{
			add_node(current, new_node, LEFT);
			current = new_node;
		}
		*token_list = (*token_list)->next;
	}
	return (root);
}
