/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:45:33 by npederen          #+#    #+#             */
/*   Updated: 2025/06/17 14:49:08 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*create_treenode(int type, char *str)
{
	t_treenode	*new_node;

	new_node = ft_calloc(1, sizeof(t_treenode));
	if (new_node == NULL)
		return (NULL);
	new_node->type = type;
	if (str)
		new_node->str = ft_strdup(str);
	new_node->argv = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
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

void	free_treenode(t_treenode *node)
{
	int	i;

	i = 0;
	if (node == NULL)
		return ;
	free_treenode(node->left);
	node->left = NULL;
	free_treenode(node->right);
	node->right = NULL;
	if (node->str != NULL)
	{
		free(node->str);
		node->str = NULL;
	}
	if (node->argv != NULL)
	{
		while (node->argv[i] != NULL)
			free(node->argv[i++]);
		free(node->argv);
		node->argv = NULL;
	}
	free(node);
	node = NULL;
}

t_treenode	*free_then_return_null(t_treenode *node)
{
	free_treenode(node);
	return (NULL);
}
