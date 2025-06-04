/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:27:07 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/04 21:43:11 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_line_node(t_token **token_list);
t_treenode	*parse_line1(t_token **token_list);
t_treenode	*parse_line2(t_token **token_list);
t_treenode	*parse_line3(t_token **token_list);

t_treenode	*parse_line_node(t_token **token_list)
{
	t_token		*tmp;
	t_treenode	*node;

	tmp = *token_list;
	node = NULL;
	node = parse_line1(token_list);
	if (node != NULL)
		return (node);
	*token_list = tmp;
	//free_treenode(node);
	node = parse_line2(token_list);
	if (node != NULL)
		return (node);
	*token_list = tmp;
	//free_treenode(node);
	node = parse_line3(token_list);
	if (node != NULL)
		return (node);
	*token_list = tmp;
	//free_treenode(node);
	return (NULL);
}

t_treenode	*parse_line1(t_token **token_list)
{
	t_treenode	*left;
	t_treenode	*right;
	t_treenode	*node;

	left = NULL;
	right = NULL;
	node = NULL;
	left = parse_logical_or_node(token_list);
	if (left == NULL)
		return (NULL);
	if (*token_list == NULL || (*token_list)->type != SEMICOLON)
	{
		//free_treenode(left);
		return (NULL);
	}
	*token_list = (*token_list)->next;
	right = parse_line_node(token_list);
	if (right == NULL)
	{
		//free_treenode(left);
		return (NULL);
	}
	node = create_treenode(SEMICOLON, ";");
	node->left = left;
	node->right = right;
	return (node);
}

t_treenode	*parse_line2(t_token **token_list)
{
	t_treenode	*left;
	t_treenode	*node;

	left = NULL;
	node = NULL;
	left = parse_logical_or_node(token_list);
	if (left == NULL)
		return (NULL);
	if (*token_list == NULL || (*token_list)->type != SEMICOLON)
	{
		//free_treenode(left);
		return (NULL);
	}
	*token_list = (*token_list)->next;
	node = create_treenode(SEMICOLON, ";");
	node->left = left;
	node->right = NULL;
	return (node);
}

t_treenode	*parse_line3(t_token **token_list)
{
	t_treenode	*node;

	node = NULL;
	return (node = parse_logical_or_node(token_list));
}
