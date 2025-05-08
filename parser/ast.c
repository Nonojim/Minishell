/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:45:33 by npederen          #+#    #+#             */
/*   Updated: 2025/05/09 00:28:34 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

/*
line          ::= semicolon;
sequence      ::= 
line          ::= pipeline (("&&" | "||") pipeline)*
pipeline      ::= command ("|" command)*
command       ::= word (word | redirection)*
word          ::= WORD | QUOTED_WORD
redirection   ::= ( ">" | ">>" | "<" | "<<" ) word
*/

t_treenode	*create_treenode(int type, char *str)
{
	t_treenode	*new_node;

	new_node = ft_calloc(1, sizeof(t_treenode));
	if (new_node == NULL)
		return (NULL);
	new_node->type = type;
	new_node->str = str;
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

void	free_treenode(t_treenode *treenode)
{
	if (!treenode)
	{
		if (treenode->str)
			free(treenode->str);
		free_treenode(treenode->left);
		free_treenode(treenode->right);
		free(treenode);
	}
}
