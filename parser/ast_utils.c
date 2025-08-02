/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:45:33 by npederen          #+#    #+#             */
/*   Updated: 2025/08/02 13:04:18 by npederen         ###   ########.fr       */
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

	if (!node)
		return ;
	free_treenode(node->left);
	free_treenode(node->right);
	if (node->argv)
	{
		i = 0;
		if (node->argv[i])
		{
			while (node->argv[i])
			{
				free_then_setnull((void **)&node->argv[i]);
				i++;
			}
		}
		free_then_setnull((void **)&node->argv);
	}
	if (node->str)
		free_then_setnull((void **)&node->str);
	free_then_setnull((void **)&node);
}

t_treenode	*free_then_return_null(t_treenode *node)
{
	free_treenode(node);
	return (NULL);
}
