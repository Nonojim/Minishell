/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_and.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:27:49 by lduflot           #+#    #+#             */
/*   Updated: 2025/05/28 11:36:29 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode *parse_logical_and_node(t_token *token_list);
t_treenode *parse_logical_and1(t_token *token_list);
t_treenode *parse_logical_and2(t_token *token_list);

//PARSE_LOGICAL_AND
t_treenode *parse_logical_and_node(t_token *token_list)
{
	t_token *tmp = token_list;
	t_treenode *node;

	if (node = parse_logical_and1(&token_list) != NULL)
		return (node);
	if (node = parse_logical_and2(&token_list) != NULL)
		return (node);
	return (NULL);
} 
t_treenode *parse_logical_and1(t_token *token_list)
{
	t_treenode *left;
	t_treenode *right;
	t_treenode *node;

	if (left = parse_logical_or_node(token_list) == NULL)
		return (NULL);

	if (token_list->type != LOGICAL_AND)
		return (NULL);
		
	if (right = parse_logical_and_node(token_list) == NULL)
		return (NULL);
	node = create_treenode(token_list->type, token_list->str);
	node->left = left;
	node->right = right;
	return (node);
}
t_treenode *parse_logical_and2(t_token *token_list)
{
	t_treenode *node;
	
	return (node = parse_logical_or_node(token_list));
}
//PARSE_LOGICAL_AND END
