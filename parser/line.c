/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:27:07 by lduflot           #+#    #+#             */
/*   Updated: 2025/05/28 11:44:44 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_line_node(t_token *token_list);
t_treenode	*parse_line1(t_token *token_list);
t_treenode	*parse_line2(t_token *token_list);
t_treenode	*parse_line3(t_token *token_list);

//PARSE_LINE_NODE
t_treenode *parse_line_node(t_token *token_list)
{
	t_token *tmp = token_list;
	t_treenode *node;

	if (node = parse_line1(&token_list) != NULL)
		return (node);
	if (node = parse_line2(&token_list) != NULL)
		return (node);
	if (node = parse_line3(&token_list) != NULL)
		return (node);
	return (NULL);
}

t_treenode	*parse_line1(t_token *token_list)
{
	t_treenode *left;
	t_treenode *right;
	t_treenode *node;

	if (left = parse_and_or(token_list) == NULL)
		return (NULL);

	if (token_list->type != SEMICOLON)
		return (NULL);
	
	if (right = parse_line(token_list) == NULL)
		return (NULL);
	node = create_treenode(token_list->type, token_list->str);
	node->left = left;
	node->right = right;
	return (node);
}

t_treenode	*parse_line2(t_token *token_list)
{
	t_treenode *left;
	t_treenode *node;

	if (left = parse_and_or(token_list) == NULL)
	return (NULL);

	if (token_list->type != SEMICOLON)
		return (NULL);

	node = create_treenode(token_list->type, token_list->str);
	node->left = left;
	node->right = NULL;
	return (node);
}

t_treenode	*parse_line3(t_token *token_list)
{
	t_treenode *node;

	return (node = parse_logical_and_node(token_list));
}
