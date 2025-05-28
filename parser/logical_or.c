/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_or.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:28:11 by lduflot           #+#    #+#             */
/*   Updated: 2025/05/28 12:14:28 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_logical_or_node(t_token *token_list);
t_treenode	*parse_logical_or1(t_token *token_list);
t_treenode	*parse_logical_or2(t_token *token_list);

t_treenode	*parse_logical_or_node(t_token *token_list)
{
	//t_token			*tmp = token_list;
	t_treenode	*node;

	if ((node = parse_logical_or1(token_list)) != NULL)
		return (node);
	if ((node = parse_logical_or2(token_list)) != NULL)
		return (node);
	return (NULL);
}

t_treenode	*parse_logical_or1(t_token *token_list)
{
	t_treenode	*left;
	t_treenode	*right;
	t_treenode	*node;

	if ((left = parse_pipeline_node(token_list)) == NULL)
		return (NULL);

	if (token_list->type != LOGICAL_OR)
		return (NULL);
		
	if ((right = parse_logical_or_node(token_list)) == NULL)
		return (NULL);
	node = create_treenode(token_list->type, token_list->str);
	node->left = left;
	node->right = right;
	return (node);
}

t_treenode	*parse_logical_or2(t_token *token_list)
{
	t_treenode	*node;
	
	return (node = parse_pipeline_node(token_list));
}
