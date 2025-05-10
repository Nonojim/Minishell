/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:45:33 by npederen          #+#    #+#             */
/*   Updated: 2025/05/10 12:43:31 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

// Fonction test pour le parsing si c'est une simple command exemple = echo hello
// Dans la grammaire simple command peut être couplé au redirection non mis dans la fonction pour l'instant
void	*parse_simple_command_without_redirection(t_token **token, t_treenode *parent_node, int dir)
{
	t_treenode *simple_command_node = NULL;
	
	if (*token->type == WORD)
	{
		if (parent_node == NULL) //if is the first node;
		{
			command_note = create_treennode(WORD, *token->str)
		}
		if (parent_node != NULL)
		{
			add_node(parent_node, command_node, dir);
			//*token = *token->right;
			//*token = *token->left
		}
	}
	else
		return ;
	return(simple_command_node);
}

// Print AST - NON FONCTIONNEL - A TRAVAILLER
void	print_ast(t_treenode *node, int dir)
{
	while(node)
	{
		if (node->left && dir == 0)
		{
			printf("/");
			printf("[%d : %s]\n", node->type, node->str);
			node = node->left;
		}
		if (node->right && dir == 1)
		{
			printf("\");
			printf("[%d : %s]\n", node->type, node->str);
			node = node->right;
		}
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
