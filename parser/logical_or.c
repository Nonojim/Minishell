/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_or.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:28:11 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/12 21:11:58 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_treenode	*parse_logical_or_node(t_token **tokens);
t_treenode	*parse_logical_or1(t_token **tokens);
t_treenode	*parse_logical_or2(t_token **tokens);


t_treenode	*parse_logical_or_node(t_token **tokens)
{
	t_token		*tmp;
	t_treenode	*or_node;

	tmp = *tokens;
	or_node = NULL;
	or_node = parse_logical_or1(tokens);
	if (or_node != NULL)
		return (or_node);
	(*tokens) = tmp;
	or_node = parse_logical_or2(tokens);
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
	t_treenode	*or_node;
	t_token		*or_token;

	left = NULL;
	right = NULL;
	or_node = NULL;

	if (*tokens == NULL || 
   ((*tokens)->type != WORD && (*tokens)->type != BRACKETS_L))
	{
		printf("minishell: syntax error near unexpected token '%s'\n", (*tokens)->str);
		return (NULL);
	}
	left = parse_logical_and_node(tokens);
	if (left == NULL)
		return (NULL);
	if (*tokens == NULL || (*tokens)->type != LOGICAL_OR)
	{
		free_treenode(left);
		return (NULL);
	}
	or_token = *tokens;
	*tokens = (*tokens)->next;
	right = parse_logical_or_node(tokens);
	if (right == NULL)
	{
		free_treenode(left);
		return (NULL);
	}
	or_node = create_treenode(or_token->type, or_token->str);
	or_node->left = left;
	if (right->type == or_token->type) // si a droite se trouve un autre ||
	{
		or_node->right = right->left;
		right->left = or_node;
		return (right);
	}
	else
	{
		or_node->right = right;
		return (or_node);
	}
}

//<logical_and>
t_treenode	*parse_logical_or2(t_token **tokens)
{
	t_treenode	*and_node;

	and_node = NULL;
	return (and_node = parse_logical_and_node(tokens));
}
