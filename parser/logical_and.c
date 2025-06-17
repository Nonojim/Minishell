/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_and.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:27:49 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/17 14:46:18 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_logical_and_node(t_token **tokens);
t_treenode	*parse_logical_and1(t_token **tokens);
t_treenode	*parse_logical_and2(t_token **tokens);
t_treenode	*create_node_logicaland(t_token *and_token,
				t_treenode *left, t_treenode *right);

t_treenode	*parse_logical_and_node(t_token **tokens)
{
	t_token		*tmp;
	t_treenode	*and_node;

	tmp = *tokens;
	and_node = NULL;
	if (parse_error(-1) == 1)
		return (NULL);
	and_node = parse_logical_and1(tokens);
	if (parse_error(-1))
		return (NULL);
	if (and_node != NULL)
		return (and_node);
	*tokens = tmp;
	and_node = parse_logical_and2(tokens);
	if (parse_error(-1) == 1)
		return (NULL);
	if (and_node != NULL)
		return (and_node);
	*tokens = tmp;
	return (NULL);
}

//<pipeline> ("||"  <pipeline> )* 
t_treenode	*parse_logical_and1(t_token **tokens)
{
	t_treenode	*left;
	t_treenode	*right;
	t_token		*and_token;

	left = NULL;
	right = NULL;
	if (*tokens == NULL || (!is_redirection((*tokens)->type)
			&& !is_bracket((*tokens)->type) && !is_word_type((*tokens)->type)))
		return (printerror_then_return_null(tokens));
	left = parse_pipeline_node(tokens);
	if (left == NULL)
		return (NULL);
	if (*tokens == NULL || (*tokens)->type != LOGICAL_AND)
		return (free_then_return_null(left));
	and_token = *tokens;
	*tokens = (*tokens)->next;
	right = parse_logical_and_node(tokens);
	if (right == NULL)
		return (free_then_return_null(left));
	return (create_node_logicaland(and_token, left, right));
}

t_treenode	*create_node_logicaland(t_token *and_token,
				t_treenode *left, t_treenode *right)
{
	t_treenode	*and_node;

	and_node = create_treenode(and_token->type, and_token->str);
	and_node->left = left;
	if (right->type == and_token->type)
	{
		and_node->right = right->left;
		right->left = and_node;
		return (right);
	}
	and_node->right = right;
	return (and_node);
}

//	<pipeline>
t_treenode	*parse_logical_and2(t_token **tokens)
{
	t_treenode	*pipe_node;

	pipe_node = NULL;
	return (pipe_node = parse_pipeline_node(tokens));
}
