/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_and.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:27:49 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/05 11:09:59 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_logical_and_node(t_token **token_list);
t_treenode	*parse_logical_and1(t_token **token_list);
t_treenode	*parse_logical_and2(t_token **token_list);

t_treenode	*parse_logical_and_node(t_token **token_list)
{
	t_token		*tmp;
	t_treenode	*node;

	tmp = *token_list;
	node = NULL;
	node = parse_logical_and1(token_list);
	if (node != NULL)
		return (node);
	*token_list = tmp;
	free_treenode(node);
	node = parse_logical_and2(token_list);
	if (node != NULL)
		return (node);
	*token_list = tmp;
	free_treenode(node);
	return (NULL);
}

//create_node = avant d'avancer dans la liste afin de créer le bon node (et pas le noeud suivant).
t_treenode	*parse_logical_and1(t_token **token_list)
{
	t_treenode	*left;
	t_treenode	*right;
	t_treenode	*node;
	t_token		*create_node;

	left = NULL;
	right = NULL;
	node = NULL;
	left = parse_pipeline_node(token_list);
	if (left == NULL)
		return (NULL);
	if (*token_list == NULL || (*token_list)->type != LOGICAL_AND)
	{
		free_treenode(left);
		return (NULL);
	}
	create_node = *token_list;
	*token_list = (*token_list)->next;
	right = parse_logical_and_node(token_list);
	if (right == NULL)
	{
		free_treenode(left);
		return (NULL);
	}
	node = create_treenode(create_node->type, create_node->str);
	node->left = left;
	if (right->type == create_node->type) // si a droite se trouve un autre &&
	{
		node->right = right->left;
		right->left = node;
		return (right);
	}
	else
	{
		node->right = right;
		return (node);
	}
}

t_treenode	*parse_logical_and2(t_token **token_list)
{
	t_treenode	*node;
	
	node = NULL;
	return (node = parse_pipeline_node(token_list));
}
