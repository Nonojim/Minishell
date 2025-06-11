/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_or.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:28:11 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/11 20:41:55 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_logical_or_node(t_token **token_list);
t_treenode	*parse_logical_or1(t_token **token_list);
t_treenode	*parse_logical_or2(t_token **token_list);


t_treenode	*parse_logical_or_node(t_token **token_list)
{
	t_token		*tmp;
	t_treenode	*node;

	tmp = *token_list;
	node = NULL;
	node = parse_logical_or1(token_list);
	if (node != NULL)
		return (node);
	(*token_list) = tmp;
	node = parse_logical_or2(token_list);
	if (node != NULL)
		return (node);
	(*token_list) = tmp;
	return (NULL);
}

//<logical_and> ("&&" <logical_and> )*
t_treenode	*parse_logical_or1(t_token **token_list)
{
	t_treenode	*left;
	t_treenode	*right;
	t_treenode	*node;
	t_token		*create_node;

	left = NULL;
	right = NULL;
	node = NULL;

	if (*token_list == NULL || 
   ((*token_list)->type != WORD && (*token_list)->type != BRACKETS_L))
	return (NULL);


	left = parse_logical_and_node(token_list);
	if (left == NULL)
		return (NULL);
	if (*token_list == NULL || (*token_list)->type != LOGICAL_OR)
	{
		free_treenode(left);
		return (NULL);
	}
	create_node = *token_list;
	*token_list = (*token_list)->next;
	right = parse_logical_or_node(token_list);
	if (right == NULL)
	{
		//free_treenode(left);
		return (NULL);
	}
	node = create_treenode(create_node->type, create_node->str);
	node->left = left;
	if (right->type == create_node->type) // si a droite se trouve un autre ||
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

//<logical_and>
t_treenode	*parse_logical_or2(t_token **token_list)
{
	t_treenode	*node;

	node = NULL;
	return (node = parse_logical_and_node(token_list));
}
