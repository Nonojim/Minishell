/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_or.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:28:11 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/18 15:02:22 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_logical_or_node(t_token **tokens);
t_treenode	*parse_logical_or1(t_token **tokens);
t_treenode	*parse_logical_or2(t_token **tokens);
t_treenode	*create_node_logicalor(t_token *or_token,
				t_treenode *left, t_treenode *right);

t_treenode	*parse_logical_or_node(t_token **tokens)
{
	t_token		*tmp;
	t_treenode	*or_node;

	tmp = *tokens;
	or_node = NULL;
	if (parse_error(-1) == 1)
		return (NULL);
	or_node = parse_logical_or1(tokens);
	if (parse_error(-1) == 1)
		return (NULL);
	if (or_node != NULL)
		return (or_node);
	(*tokens) = tmp;
	or_node = parse_logical_or2(tokens);
	if (parse_error(-1) == 1)
		return (NULL);
	if (or_node != NULL)
		return (or_node);
	(*tokens) = tmp;
	return (NULL);
}

//<logical_and> ("&&" <logical_and> )*
t_treenode	*parse_logical_or1(t_token **tokens)
{
	t_treenode	*left;
	t_treenode	*right;
	t_token		*or_token;

	left = NULL;
	right = NULL;
	if (*tokens == NULL
		|| (!is_word_type((*tokens)->type) && (*tokens)->type != BRACKETS_L
			&& !is_redirection((*tokens)->type)))
		return (printerror_then_return_null(tokens));
	left = parse_logical_and_node(tokens);
	if (left == NULL)
		return (NULL);
	if (*tokens == NULL || (*tokens)->type != LOGICAL_OR)
		return (free_then_return_null(left));
	or_token = *tokens;
	*tokens = (*tokens)->next;
	right = parse_logical_or_node(tokens);
	if (right == NULL)
		return (free_then_return_null(left));
	return (create_node_logicalor(or_token, left, right));
}

t_treenode	*create_node_logicalor(t_token *or_token,
				t_treenode *left, t_treenode *right)
{
	t_treenode	*or_node;

	or_node = create_treenode(or_token->type, or_token->str);
	or_node->left = left;
	if (right->type == or_token->type)
	{
		or_node->right = right->left;
		right->left = or_node;
		return (right);
	}
	or_node->right = right;
	return (or_node);
}

//<logical_and>
t_treenode	*parse_logical_or2(t_token **tokens)
{
	t_treenode	*and_node;

	and_node = NULL;
	return (and_node = parse_logical_and_node(tokens));
}
